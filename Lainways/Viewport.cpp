#include "Viewport.h"





Viewport::Viewport(int _x, int _y, int _width, int _height, TileMap ^ _map, Graphics ^ _canvas)
{
	ViewportWorldX = _x;
	ViewportWorldY = _y;
	viewportTilesWide = _width;
	viewportTilesHeight = _height;
	map = _map;
	canvas = _canvas;
}

/*void Viewport::ViewportMove(int _xMove, int _yMove)
{
	if (ViewportWorldX + _xMove + ((viewportTilesWide)*map->GetMapCellBitmap(0, 0)->Width) <= (map->nCols * map->GetMapCellBitmap(0, 0)->Width)) {
		if (ViewportWorldX + _xMove >= 0) {
			ViewportWorldX += _xMove;
		}
	}
	if (ViewportWorldY + _yMove + ((viewportTilesHeight)*map->GetMapCellBitmap(0, 0)->Height) <= (map->nRows * map->GetMapCellBitmap(0, 0)->Height)) {
		if (ViewportWorldY + _yMove >= 0) {
			ViewportWorldY += _yMove;
		}
	}
}*/
void Viewport::moveRelativeToPlayer(int playerWorldX, int playerWorldY)
{
	ViewportWorldX = playerWorldX - ((viewportTilesWide * map->GetMapCellBitmap(0, 0)->Width) / 2);
	ViewportWorldY = playerWorldY - ((viewportTilesHeight * map->GetMapCellBitmap(0, 0)->Height) / 2);

}

void Viewport::ViewportDraw()
{
	int startX = ViewportWorldX / map->GetMapCellBitmap(0, 0)->Width;
	int startY = ViewportWorldY / map->GetMapCellBitmap(0, 0)->Height;
	int xOffset = ViewportWorldX % map->GetMapCellBitmap(0, 0)->Width;
	int yOffset = ViewportWorldY % map->GetMapCellBitmap(0, 0)->Height;
	int locX = 0;
	int locY = 0;
	for (int c = startX; c <= startX + viewportTilesWide; c++)
	{
		for (int r = startY; r <= startY + viewportTilesHeight; r++)
		{
			if (c < map->nCols && r < map->nRows && c >= 0 && r >= 0) {
				canvas->DrawImage(map->GetMapCellBitmap(c, r), locX - xOffset, locY - yOffset);
			}
			locY += map->GetMapCellBitmap(0, 0)->Width;
		}
		locX += map->GetMapCellBitmap(0, 0)->Height;
		locY = 0;
	}
}
