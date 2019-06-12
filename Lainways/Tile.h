#pragma once
using namespace System::Drawing;
ref class Tile
{
public:
	property Bitmap^ tileBitmap;
	property bool walkable;
public:
	Tile(Bitmap^ _startingTileBitmap, bool walkable);
};

