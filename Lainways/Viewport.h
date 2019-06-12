#pragma once
#include "TileMap.h"
ref class Viewport
{
private:
	int viewportTilesWide;
	int viewportTilesHeight;
	TileMap^ map;
	Graphics^ canvas;
public:
	property int ViewportWorldX;
	property int ViewportWorldY;
public:
	Viewport(int _x, int _y, int _width, int _height, TileMap^ _map, Graphics^ _canvas);
	//void ViewportMove(int xMove, int yMove);
	void moveRelativeToPlayer(int playerWorldX, int playerWorldY);
	void ViewportDraw();
};

