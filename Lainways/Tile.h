#pragma once
using namespace System::Drawing;
ref class Tile
{
public:
	property Bitmap^ tileBitmap;
public:
	Tile(Bitmap^ _startingTileBitmap);
};

