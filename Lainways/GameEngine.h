#pragma once
#include "Tilemap.h"
#include "TileSet.h"
#include "Player.h"
#include "Viewport.h"
#include "ProjectileList.h"
#include "ItemList.h"
#include "NPCList.h"
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
	ItemList^ iL;
	NPCList^ nL;
	ProjectileList^ pL;
	Bitmap^ p1;
	int moveFrame;
	int moveDirection;
	
public:
	GameEngine(Graphics^ _canvas);
	void seedGen(String^ inpString);
	void genName();
	property int score;
	void Lose();
	void MapGen();
	void PlayerHit(int _x, int _y);
	void ViewPortGen();
	void TileInit();
	void GenerateEntities();
	void PlayerMove();
	void PlayerInit();
	void draw();
	void Keys(KeyEventArgs^ e);
	property String^ seedName;
	int NROWS = 100;
	int NCOLS = 100;
	property int state;
};




