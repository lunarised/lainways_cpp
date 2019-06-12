#pragma once
#include "Tilemap.h"
#include "TileSet.h"
#include "Player.h"
#include "Viewport.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
ref class GameEngine
{
private:
	Player^ pC;
	Viewport^ vP;
	TileSet^ ts;
	Graphics^ canvas;
	SolidBrush^ fill;
	TileMap^ tm;
public:
	GameEngine(Graphics^ _canvas);
	void seedGen(String^ inpString);
	void genName();
	void MapGen();
	void ViewPortGen();
	void TileInit();
	void PlayerInit();
	void draw();
	property String^ seedName;
	int NROWS = 100;
	int NCOLS = 100;
};




