#include "TileMap.h"
#include <vector>
#include <cmath>
//using namespace::Lainways;
typedef std::pair <int, int> point;

TileMap::TileMap(TileSet^ _tileSet, Graphics^ _startCanvas, int _startNCols, int _startNRows) {
	canvas = _startCanvas;
	nCols = _startNCols;
	nRows = _startNRows;
	tileSet = _tileSet;
	map = gcnew array<int, 2>(nCols, nRows);
	roomXarr = gcnew array<int>(NROOMS);
	roomYarr = gcnew array<int>(NROOMS);


}
void TileMap::SetMapEntry(int _col, int _row, int _tileIndex) {
	int cuck = _row;
	map[_col, _row] = _tileIndex;
}

int TileMap::GetMapEntry(int _col, int _row) {
	if (_col >= 0 && _col < nCols && _row >= 0 && _row < nRows) {
		return map[_col, _row];
	}
}

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

void TileMap::LoadMapFromFile(String^ _fName) {
	System::IO::StreamReader^ sr = System::IO::File::OpenText(_fName);
	String^ currentline = "";
	array<String^>^ indexholder = gcnew array<String^>(nCols);
	int rowCount = 0;
	while (currentline = sr->ReadLine()) {
		indexholder = currentline->Split(',');
		for (int i = 0
			; i < nCols; i++) {
			map[i, rowCount] = System::Convert::ToInt64(indexholder[i]);
		}
		rowCount++;
	}
}
Bitmap^ TileMap::GetMapCellBitmap(int _worldCol, int _worldRow) {
	int mapVal = map[_worldCol, _worldRow];
	if (mapVal <= 0) {
		Bitmap^ blank = gcnew Bitmap(32, 32);
		return blank;
	}
	Bitmap^ tileImage = tileSet->GetTileBitmap(mapVal);
	return tileImage;

}

void TileMap::Polnareff() {
	int nColsOF = nCols - 2;
	int nRowsOF = nRows - 2;
	int rad = nCols / 8;
	int k = 300;
	int w = rad / (sqrt(2));
	std::vector<Point*> aL;
	array<Point*, 2> ^ wa = gcnew array <Point*, 2>(nColsOF / w, nRowsOF / w);
	int seedX = (rand()%nColsOF - 2) + 2;
	int seedY = (rand()%nRowsOF - 2) + 2;
	while (seedX / w >= nColsOF / w || seedY / w >= nRowsOF / w) {

		seedX = (rand()%nColsOF - 2) + 2;
		seedY = (rand()%nRowsOF - 2) + 2;
	}
	aL.push_back(new Point(seedX, seedY));
	wa[aL[0]->X / w, aL[0]->Y / w] = aL[0];

	while (!aL.empty()) {
		int cuck = aL.size();
		int index = rand()%aL.size();
		bool apFail = true;
		for (int i = 0; i < 30; i++) {
			int radiusGen = (rand()%rad) + rad;
			double thetaGen = (rand()/RAND_MAX) * (2 * Math::PI);
			Point* trialpoint = new Point(radiusGen*cos(thetaGen) + aL[index]->X, radiusGen*sin(thetaGen) + aL[index]->Y);
			//THE GREAT FILTERS
			if (trialpoint->X / w < 0 || trialpoint->X / w >= nColsOF / w || trialpoint->Y / w < 0 || trialpoint->Y / w >= nRowsOF / w || wa[trialpoint->X / w, trialpoint->Y / w] != NULL) {

				continue;
			}
			if (trialpoint->X < 2 || trialpoint->X >= nColsOF || trialpoint->Y < 2 || trialpoint->Y >= nRowsOF) {
				continue;
			}

			bool failed = false;
			for (int i = (trialpoint->X / w) - 1; i <= (trialpoint->X / w) + 1; i++) {
				for (int j = (trialpoint->Y / w) - 1; j <= (trialpoint->Y / w) + 1; j++) {
					if (i >= 0 && j >= 0 && i < trialpoint->X / w && j < trialpoint->Y / w && wa[i, j] != NULL) {
						if (Math::Pow(wa[i, j]->X - trialpoint->X, 2) + Math::Pow(wa[i, j]->Y - trialpoint->Y, 2) < Math::Pow(rad, 2)) {
							failed = true;
						}
					}
				}

			}
			if (!failed) {
				aL.push_back(trialpoint);
				wa[trialpoint->X / w, trialpoint->Y / w] = trialpoint;
				apFail = false;
				break;
			}

		}
		if (apFail) {
			aL.erase(aL.begin() + index);
		}
	}
	int nRooms = 1;
	roomXarr[0] = 10;
	roomYarr[0] = 5;
	GenerateRoom(10, 5, 8, 8);
	for (int i = 0; i < nColsOF / w; i++) {
		for (int j = 0; j < nRowsOF / w; j++) {
			if (wa[i, j] != NULL) {
				if (nRooms >= NROOMS) {
					break;
				}
				int roomX = wa[i, j]->X;
				int roomY = wa[i, j]->Y;
				int roomSizeX = rand()%(nCols / 10);
				while (roomSizeX + roomX > nCols - 2) {
					roomSizeX = rand()%(nCols / 10);
				}
				int roomSizeY = rand()%(nRows / 10);
				while (roomSizeY + roomY > nRows - 2) {
					roomSizeY = rand()%(nRows / 10);
				}
				GenerateRoom(roomX, roomY, roomSizeX, roomSizeY);
				roomXarr[nRooms] = roomX + (roomSizeX / 2);
				roomYarr[nRooms] = roomY + (roomSizeY / 2);
				nRooms++;

			}
		}
	}
}

void TileMap::GenerateMap(int _ncols, int _nrows) {
	//SET DIMENSIONS
	int NCOLS = _ncols;
	int NROWS = _nrows;
	//GENERATE ROOMS
	Polnareff();
	//GENERATE CORRIDORS
	for (int i = 0; i < NROOMS - 1; i++) {
		GenerateCorridor(roomXarr[i], roomXarr[i + 1], roomYarr[i], roomYarr[i + 1]);
	}
	GenerateFeats();
}
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
	//Horz Right

	for (int i = _x1; i <= _x2; i++) {
		//	if (GetMapEntry(i, _y1 + 1) != 2) {
		//		SetMapEntry(i, _y1 + 1, 1);
		//	}
		//	if (GetMapEntry(i, _y1 -1) != 2) {
		//		SetMapEntry(i, _y1 -1, 1);
		//	}
		SetMapEntry(i, _y1, -2);
	}

	//Horiz Left

//Vert Down
	if (_y1 < _y2) {
		for (int i = _y1; i <= _y2; i++) {
			//if (GetMapEntry( _x2 +1, i) != 2) {
			//	SetMapEntry( _x2 + 1 , i, 1);
			//}
			//if (GetMapEntry(_x2 -1, i) != 2) {
			//	SetMapEntry(_x2 - 1 ,i , 1);
			//}
			SetMapEntry(_x2, i, -2);
		}
	}
	//Vert Up
	else {
		for (int i = _y2; i <= _y1; i++) {
			//if (GetMapEntry( _x2 + 1,i) != 2) {
			//	SetMapEntry( _x2 + 1,i, 1);
			//}
			//if (GetMapEntry( _x2 - 1,i) != 2) {
			//	SetMapEntry( _x2 - 1,i, 1);
			//}
			SetMapEntry(_x2, i, -2);
		}
	}


}
void TileMap::GenerateRoom(int _x, int _y, int _w, int _h) {
	for (int i = 0; i <= _w; i++) {
		//	if (GetMapEntry(i + _x, _y) != 2) {
		//		SetMapEntry(i + _x, _y, 1);
		//	}
		if (i != 0 && i != _w) {
			for (int j = _y + 1; j < _y + _h; j++) {
				SetMapEntry(i + _x, j, -2);
			}
		}
		//if (GetMapEntry(i + _x, _y + _h) != 2) {
		//	SetMapEntry(i + _x, _y + _h, 1);
		//}

	}
	for (int i = 0; i <= _h; i++) {
		//if (GetMapEntry(_x, _y + i) != 2) {
		//	SetMapEntry(_x, _y + i, 1);
		//}
		//if (GetMapEntry(_w + _x, _y + i) != 2) {
		//	SetMapEntry(_w + _x, _y + i, 1);
		//}

	}
}
void TileMap::GenerateFeats() {
	for (int i = 1; i < nCols - 1; i++) {
		for (int j = 1; j < nRows - 1; j++) {
			if (abs(GetMapEntry(i, j)) == 2) {
				if (rand()%(50) == 0) {
				//	TileForm::instance->putCoin(i * 32, j * 32);
				}
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
	for (int i = 1; i < nCols - 1; i++) {
		for (int j = 1; j < nRows - 1; j++) {
			bool nullneighbor = false;
			if (abs(GetMapEntry(i, j)) == 1) {
				//if (r->Next(50) == 0) {
				//TileForm::instance->putCoin(i * 32, j * 32);
				//}
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