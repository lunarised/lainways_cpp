#pragma once
#include "NPC.h"
#include <cmath>


NPC::NPC(Graphics^ _canvas, Bitmap^ _spriteSheet, int _frameWidth, int _frameHeight, int _nFrames, int _xPos, int _yPos, int _Type) {
	canvas = _canvas;
	frameHeight = _frameHeight;
	frameWidth = _frameWidth;
	nFrames = _nFrames;
	spriteSheet = _spriteSheet;
	xPos = _xPos;
	yPos = _yPos;
	Type = _Type;
	direction = rand() % 4;
	if (_Type == 1) {
		health = rand() % 10 + 1;
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
