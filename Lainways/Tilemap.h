#pragma once
#include "TileSet.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
ref class TileMap
{
private:
	TileSet^ tileSet;
	array<int, 2>^ map;
	Graphics^ canvas;
	array<int>^ roomXarr;
	array<int>^ roomYarr;
public:
	TileMap(TileSet^ _tileSet, Graphics^ _startCanvas, int _startNRows, int _startNCols);
	void SetMapEntry(int _col, int _row, int _tileIndex);
	void GenerateMap(int _ncols, int _nrows);
	void GenerateRoom(int _x, int _y, int _width, int _height);
	int GetMapEntry(int _col, int _row);
	void GenerateCorridor(int _x1, int _x2, int _y1, int _y2);
	void GenerateFeats();
	void DrawMap();
	Bitmap^ GetMapCellBitmap(int _worldRow, int _worldCol);
	int nCols;
 int nRows;
	const int NROOMS = 225;
	void PoissonGen();
};

