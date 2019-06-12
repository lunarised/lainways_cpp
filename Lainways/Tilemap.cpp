#include "TileMap.h"
#include <vector>
#include <cmath>
typedef std::pair <int, int> point; //For GNU C++ conversion

/*A Class for all things map related*/
TileMap::TileMap(TileSet^ _tileSet, Graphics^ _startCanvas, int _startNCols, int _startNRows) {
	canvas = _startCanvas;
	nCols = _startNCols;
	nRows = _startNRows;
	tileSet = _tileSet;
	map = gcnew array<int, 2>(nCols, nRows);
	roomXarr = gcnew array<int>(NROOMS);
	roomYarr = gcnew array<int>(NROOMS);
}
/*Sets a maps tile to a specified tile*/
void TileMap::SetMapEntry(int _col, int _row, int _tileIndex) {
	map[_col, _row] = _tileIndex;
}
/*Reads what tile is at a position*/
int TileMap::GetMapEntry(int _col, int _row) {
	if (_col >= 0 && _col < nCols && _row >= 0 && _row < nRows) {
		return map[_col, _row];
	}
}
/*Draws the map*/
void TileMap::DrawMap() {
	for (int row = 0; row < nRows; row++) {
		for (int col = 0; col < nCols; col++) {
			Bitmap^ currentTile = tileSet->GetTileBitmap(abs(GetMapEntry(col, row)));
			if (GetMapEntry(col, row) > 0) {
				canvas->DrawImage(currentTile, col*currentTile->Width, row*currentTile->Height);
			}
		}
	}
}
/*Get the bitmap of a cell*/
Bitmap^ TileMap::GetMapCellBitmap(int _worldCol, int _worldRow) {
	int mapVal = map[_worldCol, _worldRow];
	if (mapVal <= 0) {//If unknown give it a transparent bitmap
		return tileSet->GetTileBitmap(0);
	}
	return tileSet->GetTileBitmap(mapVal);
}
/* Distributes rooms randomly but still evenly
Based heavily on the Poisson Distribution
Excessive Commenting due to low readability
*/
void TileMap::PoissonGen() {
	int nColsOF = nCols - 2; //Gives us a 2 buffer zone
	int nRowsOF = nRows - 2; //Gives us a 2 buffer zone
	int rad = nCols / 8; //We dont want more than 7 rooms on either axis
	int k = 300; // Retry to put in the rooms K times
	int w = rad / (sqrt(2)); //just a mathy constant
	std::vector<Point*> aL; // a vector where we store all points that could potentially spawn a room
	array<Point*, 2> ^ wa = gcnew array <Point*, 2>(nColsOF / w, nRowsOF / w); // a grid that represents the room areas
	int seedX = (rand()%nColsOF - 2) + 2;// More buffer
	int seedY = (rand()%nRowsOF - 2) + 2;// More buffer
	while (seedX / w >= nColsOF / w || seedY / w >= nRowsOF / w) {//While we havent found a nice place to gen the first room
		seedX = (rand()%nColsOF - 2) + 2;//Gen an X value
		seedY = (rand()%nRowsOF - 2) + 2;//Gen a Y Value
	}
	aL.push_back(new Point(seedX, seedY));//Add this new point to the active vector
	wa[aL[0]->X / w, aL[0]->Y / w] = aL[0];//Add this point to its corresponding cell in the matrix
	while (!aL.empty()) { // While there is potential for more rooms
		int index = rand()%aL.size(); //Get a random room from the vector of active rooms
		bool apFail = true; //Assume the active point cant find any more active points
		for (int i = 0; i < k; i++) { // Try k times to find a new point by
			int radiusGen = (rand()%rad) + rad; //Getting a distance away from the first point, between rad and 2rad
			double fGen = ((double)rand() / RAND_MAX);//getting a random double between 0 and 1 so
			double thetaGen = fGen * (2 * Math::PI);//we can get a random angle from 0 to 2pi
			Point* trialpoint = new Point(radiusGen*cos(thetaGen) + aL[index]->X, radiusGen*sin(thetaGen) + aL[index]->Y);//Get the XY value of this new tried room
			//THE GREAT FILTERS for Bounds and Edge Casing
			if (trialpoint->X / w < 0 || trialpoint->X / w >= nColsOF / w || trialpoint->Y / w < 0 || trialpoint->Y / w >= nRowsOF / w || wa[trialpoint->X / w, trialpoint->Y / w] != NULL) {
				
				continue;//Its failed, go back to the for loop
			}
			if (trialpoint->X < 2 || trialpoint->X >= nColsOF || trialpoint->Y < 2 || trialpoint->Y >= nRowsOF) {
				continue;
			}

			bool failed = false; //assume that the new point is not within r of any other point
			for (int i = (trialpoint->X / w) - 1; i <= (trialpoint->X / w) + 1; i++) {
				for (int j = (trialpoint->Y / w) - 1; j <= (trialpoint->Y / w) + 1; j++) {//Check every other point
					if (i >= 0 && j >= 0 && i < trialpoint->X / w && j < trialpoint->Y / w && wa[i, j] != NULL) {
						if (Math::Pow(wa[i, j]->X - trialpoint->X, 2) + Math::Pow(wa[i, j]->Y - trialpoint->Y, 2) < Math::Pow(rad, 2)) {//if its closer than r to the attempted gen point
							failed = true;// the gen point fails
						}
					}
				}

			}
			if (!failed) {//if the gen point didnt fail
				aL.push_back(trialpoint);//its now an active point add it to the vector of active points
				wa[trialpoint->X / w, trialpoint->Y / w] = trialpoint;//add it to its corrisponding grid cell
				apFail = false;// it didnt fail. Stop trying for more (using k)
				break;
			}
		}
		if (apFail) {//if all K attempts failed
			aL.erase(aL.begin() + index); // the point is no longer active
		}
	}
	int nRooms = 1; //start the room iterator at 1 (0 is for spawn)
	roomXarr[0] = 10;//set spawn X
	roomYarr[0] = 5;//set spawn Y
	GenerateRoom(10, 5, 8, 8); // Generate spawn room
	for (int i = 0; i < nColsOF / w; i++) {
		for (int j = 0; j < nRowsOF / w; j++) {//for each genned room in the grid
			if (wa[i, j] != NULL) { //dont read from a NULL value
				if (nRooms >= NROOMS) { //Upper cap on rooms incase silliness ensues
					break;
				}
				int roomX = wa[i, j]->X;//copy the rooms xvalue
				int roomY = wa[i, j]->Y;//copy the rooms y vale
				int roomSizeX = rand()%(nCols / 10);
				while (roomSizeX + roomX > nCols - 2) {//keep genning size
					roomSizeX = rand()%(nCols / 10);
				}
				int roomSizeY = rand()%(nRows / 10);
				while (roomSizeY + roomY > nRows - 2) {//keep genning size
					roomSizeY = rand()%(nRows / 10);
				}
				GenerateRoom(roomX, roomY, roomSizeX, roomSizeY);//generate the room
				roomXarr[nRooms] = roomX + (roomSizeX / 2);//add its X to the corridor array tracker
				roomYarr[nRooms] = roomY + (roomSizeY / 2);//add its Y to the corridor array tracker
				nRooms++; //iterate

			}
		}
	}
}
/* Big wrapper for generating the map*/
void TileMap::GenerateMap(int _ncols, int _nrows) {
	//SET DIMENSIONS
	int NCOLS = _ncols;
	int NROWS = _nrows;
	//GENERATE ROOMS
	PoissonGen();
	//GENERATE CORRIDORS
	for (int i = 0; i < NROOMS - 1; i++) {
		GenerateCorridor(roomXarr[i], roomXarr[i + 1], roomYarr[i], roomYarr[i + 1]);
	}
	//Generate walls
	GenerateFeats();
}
/*Generates Corridors between rooms*/
void TileMap::GenerateCorridor(int _x1, int _x2, int _y1, int _y2) {
	if (_x1 < 3 || _x2 < 3) {
		return;
	}
	if (_x1 > _x2) {
		int hold = _x2;
		_x2 = _x1;
		_x1 = hold;
		hold = _y2;
		_y2 = _y1;
		_y1 = hold;
	}
	//Horz generation
	for (int i = _x1; i <= _x2; i++) {
		SetMapEntry(i, _y1, -2);
	}
//Vert Down
	if (_y1 < _y2) {
		for (int i = _y1; i <= _y2; i++) {
			SetMapEntry(_x2, i, -2);
		}
	}
	//Vert Up
	else {
		for (int i = _y2; i <= _y1; i++) {
			SetMapEntry(_x2, i, -2);
		}
	}
}
/*Generates the initial flooring for the room*/
void TileMap::GenerateRoom(int _x, int _y, int _w, int _h) {
	for (int i = 0; i <= _w; i++) {
		if (i != 0 && i != _w) {
			for (int j = _y + 1; j < _y + _h; j++) {
				SetMapEntry(i + _x, j, -2);
			}
		}
	}
}
/*Generates the Walls, and removes "Floating" walls */
void TileMap::GenerateFeats() {
	//Generates walls
	for (int i = 1; i < nCols - 1; i++) {
		for (int j = 1; j < nRows - 1; j++) {
			if (abs(GetMapEntry(i, j)) == 2) {
				
				if (GetMapEntry(i - 1, j) == 0) {
					SetMapEntry(i - 1, j, -1);
				}
				if (GetMapEntry(i - 1, j - 1) == 0) {
					SetMapEntry(i - 1, j - 1, -1);
				}
				if (GetMapEntry(i - 1, j + 1) == 0) {
					SetMapEntry(i - 1, j + 1, -1);
				}
				if (GetMapEntry(i + 1, j) == 0) {
					SetMapEntry(i + 1, j, -1);
				}
				if (GetMapEntry(i + 1, j - 1) == 0) {
					SetMapEntry(i + 1, j - 1, -1);
				}
				if (GetMapEntry(i + 1, j + 1) == 0) {
					SetMapEntry(i + 1, j + 1, -1);
				}
				if (GetMapEntry(i, j - 1) == 0) {
					SetMapEntry(i, j - 1, -1);
				}
				if (GetMapEntry(i, j + 1) == 0) {
					SetMapEntry(i, j + 1, -1);
				}
			}
		}
	}
	//Removes floating walls, if it doesnt have a non tile neighbor
	for (int i = 1; i < nCols - 1; i++) {
		for (int j = 1; j < nRows - 1; j++) {
			bool nullneighbor = false;
			if (abs(GetMapEntry(i, j)) == 1) {
				
				if (GetMapEntry(i - 1, j) == 0) {
					nullneighbor = true;
				}
				if (GetMapEntry(i - 1, j - 1) == 0) {
					nullneighbor = true;
				}
				if (GetMapEntry(i - 1, j + 1) == 0) {
					nullneighbor = true;
				}
				if (GetMapEntry(i + 1, j) == 0) {
					nullneighbor = true;
				}
				if (GetMapEntry(i + 1, j - 1) == 0) {
					nullneighbor = true;
				}
				if (GetMapEntry(i + 1, j + 1) == 0) {
					nullneighbor = true;
				}
				if (GetMapEntry(i, j - 1) == 0) {
					nullneighbor = true;
				}
				if (GetMapEntry(i, j + 1) == 0) {
					nullneighbor = true;
				}
				if (!nullneighbor) {
					SetMapEntry(i, j, -2);
				}
			}
		}
	}
}