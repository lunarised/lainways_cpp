#include "Player.h"
#define SPEED 32


Player::Player(Graphics^ _canvas, Bitmap^ _spriteSheet, int _nFrames)
{
	canvas = _canvas;
	spriteSheet = _spriteSheet;
	nFrames = _nFrames;
	frameWidth = 32;
	frameHeight = 32;
	xPos = 416;// 800 / 2 - (frameWidth / 2);
	yPos = 320;//600 / 2 - (frameHeight / 2);
	currentFrame = 0;
	direction = 0;
}
void Player::draw() {
	Rectangle pixelsToDraw = Rectangle(currentFrame*frameWidth, 0, frameWidth, frameHeight);
	canvas->DrawImage(spriteSheet, xPos, yPos, pixelsToDraw, GraphicsUnit::Pixel);
}
void Player::Pickup(ItemList^ _IL) {
	_IL->Pickup(xPos, yPos);
}

void Player::forceDraw(int _x, int _y) {
	Rectangle pixelsToDraw = Rectangle(currentFrame*frameWidth, frameHeight*direction, frameWidth, frameHeight);
	canvas->DrawImage(spriteSheet, _x, _y, pixelsToDraw, GraphicsUnit::Pixel);
}
void Player::move(int _direction) {
	direction = _direction;
	switch (_direction) {
	case 0:

		yPos += SPEED;
		break;
	case 1:
		xPos += SPEED;
		break;
	case 2:
		xPos -= SPEED;
		break;
	case 3:
		yPos -= SPEED;
		break;
	}

}
void Player::rotate(int _direction) {
	direction = _direction;
}
void Player::boundsCheck() {
	if (xPos > 800) {
		xPos = 0 - frameWidth;
	}
	if (xPos < 0 - frameWidth) {
		xPos = 800;
	}
	if (yPos > 600 + frameHeight) {
		yPos %= 600;
	}
	if (yPos < 0 - frameHeight) {
		yPos = 600;
	}

}
void Player::discover(TileMap^ tm, int nCols, int nRows) {
	for (int i = -3; i <= 3; i++) {
		for (int j = -3; j <= 3; j++) {
			if (xPos / 32 + i > 0 && yPos / 32 + j > 0 && xPos / 32 + i < nCols && yPos / 32 + j < nRows) {
				tm->SetMapEntry(xPos / 32 + i, yPos / 32 + j, Math::Abs(tm->GetMapEntry(xPos / 32 + i, yPos / 32 + j)));
			}
		}
	}

}
void Player::updateFrame() {
	currentFrame = (currentFrame + 1) % nFrames;
}
void Player::setSpriteSheet(Bitmap^ _spriteSheet, int _nFrames) {
	nFrames = _nFrames;
	spriteSheet = _spriteSheet;
	frameHeight = spriteSheet->Height;
	frameWidth = (spriteSheet->Width) / nFrames;
}