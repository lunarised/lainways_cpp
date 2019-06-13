#pragma once
#include "Projectile.h"
#include <cmath>

Projectile::Projectile(Graphics^ _canvas, Bitmap^ _spriteSheet, int _frameWidth, int _frameHeight, int _nFrames, int _xPos, int _yPos, int _speed, int _dmg, int _dir) {
	canvas = _canvas;
	frameHeight = _frameHeight;
	frameWidth = _frameWidth;
	nFrames = _nFrames;
	spriteSheet = _spriteSheet;
	xPos = _xPos;
	yPos = _yPos;
	dmg = _dmg;
	speed = _speed;//Not yet implemented.
	dir = _dir;
}
void Projectile::draw(int _xVP, int _yVP) {
	if (xPos > _xVP - frameWidth && yPos > _yVP - frameHeight && xPos < _xVP + 800 && yPos < _yVP + 600) {
		Rectangle pixelsToDraw = Rectangle(currentFrame*frameWidth, 0, frameWidth, frameHeight);
		canvas->DrawImage(spriteSheet, (xPos - _xVP)+8, yPos - _yVP +8, pixelsToDraw, GraphicsUnit::Pixel);
	}
}

void Projectile::move() {
	if (dir == 0) {
		yPos += 32;
	}
	if (dir == 1) {
		xPos += 32;
	}
	if (dir == 2) {
		xPos -= 32;
	}
	if (dir == 3) {
		yPos -= 32;
	}
}


void Projectile::updateFrame() {
	currentFrame = (currentFrame + 1) % nFrames;
}
