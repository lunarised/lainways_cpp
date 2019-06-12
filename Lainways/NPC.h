#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class NPC
{
private:

	int frameHeight;
	int frameWidth;
	int nFrames;
	int currentFrame;
	Graphics^ canvas;
	Bitmap^ spriteSheet;
public:
	NPC^ Next;
	property int xPos;
	property int yPos;
	property int Type;

public:
	NPC(Graphics^ _canvas, Bitmap^ _spriteSheet, int _frameWidth, int _frameHeight, int _nFrames, int _xPos, int _yPos, int type);
	void draw(int _xVP, int _yVP);
	void updateFrame();
	int direction;
};

