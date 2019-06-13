#pragma once
#include "NPC.h"
#include <cmath>


NPC::NPC(Graphics^ _canvas, Bitmap^ _spriteSheet, int _frameWidth, int _frameHeight, int _nFrames, int _xPos, int _yPos, int _Type, TileMap^ _tm) {
	canvas = _canvas;
	frameHeight = _frameHeight;
	frameWidth = _frameWidth;
	tm = _tm;
	nFrames = _nFrames;
	spriteSheet = _spriteSheet;
	xPos = _xPos;
	yPos = _yPos;
	Type = _Type;
	state = 0;
	direction = rand() % 4;
	if (_Type == 1) {
		health = rand() % 10 + 1;
	}
}
void NPC::genState(int _x, int _y) {
	if (xPos < _x + 256 && xPos > _x - 256 && yPos < _y + 256 && yPos > _y - 256) {
		if (health > 2) {
			state = 1;//Aggro
		}
		else {
			state = 2;//Flee
		}
	}
	else {
		state = 0;//Idle	
	}
}
int NPC::action(int _x, int _y) {
	if (state == 0) {
		health += (health < 6) ? rand() % 3 : 0;
	}
	if (state == 1) {
		int xD, yD = 0;
		int xDir, yDir = 0;
		if (xPos - _x > 0) {
			xD = Math::Abs(xPos - _x);
			xDir = 2;
			//face left
		}
		else if (xPos - _x < 0) {
			//face right
			xD = Math::Abs(xPos - _x);
			xDir = 1;
		}
		if (yPos - _y > 0) {
			//face up
			yD = Math::Abs(yPos - _y);
			yDir = 3;
		}
		else if (yPos - _y < 0) {
			yD = Math::Abs(yPos - _y);
			yDir = 0;
			//facedown
		}
		if (xD > yD) {
			direction = xDir;
		}
		else {
			direction = yDir;
		}
		if (Math::Abs(tm->GetMapEntry((xPos / 32), (yPos / 32) + 1)) >= 2 && direction == 0) {
			if (_x == xPos && _y  == yPos + 32) {
				return rand() % 4;
			}
			else {
				yPos += 32;
			}
		}
		else if (Math::Abs(tm->GetMapEntry((xPos / 32) + 1, (yPos / 32))) >= 2 && direction == 1) {
			if (_x== xPos + 32 && _y  == yPos) {
				return rand() % 4;
			}
			else {
				xPos += 32;
			}
		}
		else if (Math::Abs(tm->GetMapEntry((xPos / 32) - 1, (yPos / 32))) >= 2 && direction == 2) {
			if (_x  == xPos - 32 && _y == yPos ) {
				return rand() % 4;
			}
			else {
				xPos -= 32;
			}
		}
		else if (Math::Abs(tm->GetMapEntry((xPos / 32), (yPos / 32) - 1)) >= 2 && direction == 3) {
			if (_x == xPos && _y  == yPos - 32) {
				return rand() % 4;
			}
			else {
				yPos -= 32;
			}
		}
	}
	if (state == 2) {
		int xD, yD = 0;
		int xDir, yDir = 0;
		if (xPos - _x > 0) {
			xD = Math::Abs(xPos - _x);
			xDir = 1;
			//face left
		}
		else if (xPos - _x < 0) {
			//face right
			xD = Math::Abs(xPos - _x);
			xDir = 2;
		}
		if (yPos - _y > 0) {
			//face up
			yD = Math::Abs(yPos - _y);
			yDir = 0;
		}
		else if (yPos - _y < 0) {
			yD = Math::Abs(yPos - _y);
			yDir = 3;
			//facedown
		}
		if (xD > yD) {
			direction = xDir;
		}
		else {
			direction = yDir;
		}
		if (Math::Abs(tm->GetMapEntry((xPos / 32), (yPos / 32) - 1)) >= 2 && direction == 0) {
			yPos -= 32;
		}
		else if (Math::Abs(tm->GetMapEntry((xPos / 32) - 1, (yPos / 32))) >= 2 && direction == 1) {
				xPos -= 32;
		}
		else if (Math::Abs(tm->GetMapEntry((xPos / 32) + 1, (yPos / 32))) >= 2 && direction == 2) {	
				xPos += 32;
		}
		else if (Math::Abs(tm->GetMapEntry((xPos / 32), (yPos / 32) + 1)) >= 2 && direction == 3) {
				yPos += 32;
		}
	}
}
void NPC::draw(int _xVP, int _yVP) {
	if (xPos > _xVP - frameWidth && yPos > _yVP - frameHeight && xPos < _xVP + 800 && yPos < _yVP + 600) {
		Rectangle pixelsToDraw = Rectangle(direction*frameWidth, 0, frameWidth, frameHeight);
		canvas->DrawImage(spriteSheet, (xPos - _xVP) , yPos - _yVP , pixelsToDraw, GraphicsUnit::Pixel);
	}
}

void NPC::updateFrame() {
	currentFrame = (currentFrame + 1) % nFrames;
}
