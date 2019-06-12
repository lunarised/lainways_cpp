#include "Tile.h"



Tile::Tile(Bitmap^ _tileBitmap, bool _walkable)
{
	walkable = _walkable;
	tileBitmap = _tileBitmap;
}
