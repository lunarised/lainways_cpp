#include "Item.h"
#define WANDERP 20
Item::Item(Graphics^ _canvas, array<Bitmap^>^ _spriteSheet, int _nFrames, int _frameWidth, int _frameHeight) {
	canvas = _canvas;
	//spriteSheet = _spriteSheet;
	nFrames = _nFrames;
	frameHeight = _frameHeight;
	frameWidth = _frameWidth;
	//currentFrame = rGen->Next(nFrames);


}
Item::Item(Graphics^ _canvas, Bitmap^ _spriteSheet, int _frameWidth, int _frameHeight, int _nFrames, int _xPos, int _yPos, int _Type) {
	canvas = _canvas;
	frameHeight = _frameHeight;
	frameWidth = _frameWidth;
	nFrames = _nFrames;
	spriteSheet = _spriteSheet;
	xPos = _xPos;
	yPos = _yPos;
	Type = _Type;


}
void Item::draw(int _xVP, int _yVP) {
	if (xPos > _xVP - frameWidth && yPos > _yVP - frameHeight && xPos < _xVP + 800 && yPos < _yVP + 600) {
		Rectangle pixelsToDraw = Rectangle(currentFrame*frameWidth, 0, frameWidth, frameHeight);
		canvas->DrawImage(spriteSheet, (xPos - _xVP) + (frameWidth / 2), yPos - _yVP + (frameHeight / 2), pixelsToDraw, GraphicsUnit::Pixel);
	}
}




void Item::updateFrame() {
	currentFrame = (currentFrame + 1) % nFrames;
}
