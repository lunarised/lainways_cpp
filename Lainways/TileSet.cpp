#include "TileSet.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

TileSet::TileSet(int _nTiles)
{
	nTiles = _nTiles;
	tileArray = gcnew array<Tile^>(nTiles);
}

Bitmap^ TileSet::GetTileBitmap(int _tileIndex) {
	return tileArray[_tileIndex]->tileBitmap;
}
bool TileSet::GetWalkable(int _tileIndex) {
	if (_tileIndex < nTiles) {
		return tileArray[Math::Abs(_tileIndex)]->walkable;
	}
	else {
		return false;
	}
}

void TileSet::SetTileArrayEntry(int _arrayN, Tile^ _tileToInsert) {
	tileArray[_arrayN] = _tileToInsert;
}