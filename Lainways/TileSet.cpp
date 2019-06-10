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

void TileSet::SetTileArrayEntry(int _arrayN, Tile^ _tileToInsert) {
	tileArray[_arrayN] = _tileToInsert;
}