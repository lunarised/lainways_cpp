#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Projectile
{
private:

	int frameHeight;
	int frameWidth;
	int nFrames;
	int currentFrame;
	Graphics^ canvas;
	Bitmap^ spriteSheet;
public:
	Projectile^ Next;
	property int xPos;
	property int yPos;
	property int Type;
	property int dmg;
	property int speed;
	property int dir;
	property bool alive;


public:
	Projectile(Graphics^ _canvas, Bitmap^ _spriteSheet, int _frameWidth, int _frameHeight, int _nFrames, int _xPos, int _yPos, int _speed, int _dmg, int _dir);
	void draw(int _xVP, int _yVP);
	void updateFrame();
	void move();
};

