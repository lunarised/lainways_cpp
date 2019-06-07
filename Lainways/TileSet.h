#pragma once
#include"Tile.h"
ref class TileSet
{
private:
	array<Tile^>^ tileArray;
	int nTiles;
public:
	TileSet(int _nTiles);
	Bitmap^ GetTileBitmap(int _tileIndex);
	void SetTileArrayEntry(int _arrayN, Tile^ _tileToInsert);
};

