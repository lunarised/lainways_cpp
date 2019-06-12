#pragma once
#include "ItemList.h"
#include "TileMap.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
ref class Player
{
public:
	Player(Graphics^ _canvas, Bitmap^ _spriteSheet, int _nFrames);
	void draw();
	void forceDraw(int _x, int _y);
	void move(int _direction, int px);
	void updateFrame();
	int Pickup(ItemList^ _iL);
	void setSpriteSheet(Bitmap^ _spriteSheet, int _nFrames);
	void boundsCheck();
	void discover(TileMap^ tm, int nCols, int nRows);
	property int xPos;
	property int yPos;
	void rotate(int _direction);
private:

	int direction;
	int currentFrame;
	int frameHeight;
	int frameWidth;
	int nFrames;
	Bitmap^ spriteSheet;
	Graphics^ canvas;
};

