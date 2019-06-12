#include "GameEngine.h"
#include <cstdlib> 
#include <time.h>
GameEngine::GameEngine(Graphics^ _canvas)
{
	score = 80;
	state = 0;
	moveDirection = 0;
	moveFrame = 15;
	canvas = _canvas;
	fill = gcnew SolidBrush(Color::Aqua);
	
	

}
void GameEngine::Lose() {

}
void GameEngine::seedGen(String^ inpString) {
	inpString = inpString->ToLower();
	int n = 0;
	for (int i = 0; i < inpString->Length; i++) {
		int ab = inpString[i];
		if (ab == 32) {
			ab = 96;
		}
		n += ((ab - 96) *((i + 1) * 27))%716559;
		n %= 716559;
	}
	srand(n);
}
 void GameEngine::genName(){
	srand(time(0));
	int p = rand()%72;
	int s = rand()%59;
	System::IO::StreamReader^ sr = System::IO::File::OpenText("p.txt");
	for (int i = 0; i < p; i++){
		sr->ReadLine();
	}
	String^ pr = sr->ReadLine();
	System::IO::StreamReader^ srs = System::IO::File::OpenText("s.txt");
	for (int i = 0; i < s; i++) {
		srs->ReadLine();
	}
	String^ su = srs->ReadLine();
	seedName = (pr + " " + su);
}
 void GameEngine::draw() {
	 //pC->updateFrame();
	 pC->discover(tm, NCOLS, NROWS);
	 vP->moveRelativeToPlayer(pC->xPos, pC->yPos);
	 vP->ViewportDraw();
	 iL->drawItems(vP->ViewportWorldX, vP->ViewportWorldY);
	 nL->drawNPC(vP->ViewportWorldX, vP->ViewportWorldY);
	 pC->forceDraw(400, 304);
	 

 }
 void GameEngine::TileInit() {
	 Tile^ cobble = gcnew Tile(gcnew Bitmap("cobble.bmp"), true);
	 Tile^ flower = gcnew Tile(gcnew Bitmap("flower.bmp"), false);
	 Tile^ grass = gcnew Tile(gcnew Bitmap("floor0.bmp"), true);
	 Tile^ blank = gcnew Tile(gcnew Bitmap(32, 32), false);
	 ts = gcnew TileSet(4);
	 ts->SetTileArrayEntry(0, blank);
	 ts->SetTileArrayEntry(3, cobble);
	 ts->SetTileArrayEntry(1, flower);
	 ts->SetTileArrayEntry(2, grass);
 }
 void GameEngine::MapGen() {
	 tm = gcnew TileMap(ts, canvas, NROWS, NCOLS);
	 iL = gcnew ItemList(tm);
	 nL = gcnew NPCList(tm);
	 tm->GenerateMap(NROWS, NCOLS);
	 
 }
 void GameEngine::PlayerInit() {
	 Bitmap^ pCI = gcnew Bitmap("Player.bmp");
	 Color tC = pCI->GetPixel(0, 0);
	 pCI->MakeTransparent(tC);
	 pC = gcnew Player(canvas, pCI, 3);
 }
 void GameEngine::ViewPortGen() {
	 vP = gcnew Viewport(0, 0, 25, 19, tm, canvas);
	 vP->ViewportDraw();
 }
 void GameEngine::GenerateEntities() {
	 Bitmap^ coin = gcnew Bitmap("USBStick.bmp");
	 Color tC = coin->GetPixel(0, 0);
	 coin->MakeTransparent(tC);
	 Bitmap^ camera = gcnew Bitmap("Camera.bmp");
	 tC = camera->GetPixel(0, 0);
	 camera->MakeTransparent(tC);

	 for (int i = 1; i < NCOLS - 1; i++) {
		 for (int j = 1; j < NROWS - 1; j++) {
			 if (abs(tm->GetMapEntry(i, j)) == 2) {
				 if (rand() % 40 == 0) {
					 iL->addItem(gcnew Item(canvas, coin, 16, 16, 1, i * 32, j * 32, 1));
				 }
				 else if (rand() % 200 == 0) {
					 nL->addNPC(gcnew NPC(canvas, camera, 32, 32, 1, i * 32, j * 32, 1));
				 }
			 }
		 }
	 }

 }
 void GameEngine::PlayerHit(){}
 void GameEngine::PlayerMove() {
	 if (moveFrame != 15) {
		 if (moveFrame == 0 || moveFrame == 14) {
			 pC->move(moveDirection, 3);
		 }
		 
		 else {
			 pC->move(moveDirection, 2);
		 }
		 if (moveFrame == 0 || moveFrame == 8 || moveFrame == 14) {
			 pC->updateFrame();
		 }
		 moveFrame++;
	 }
	 else {
		 int item = pC->Pickup(iL);
		 if (item == 1) {
			 score += 40;
		 }
	 }
 }
 void GameEngine::Keys(KeyEventArgs^ e) {
	 if (state == 1) {
		 if (moveFrame == 15 && score > 0) {
			 
			 if (e->KeyData == Keys::Left) {
				 //if you can move to the left sided tile
				 if (nL->Collide(pC->xPos - 32, pC->yPos)) {
					 PlayerHit();
				 }
				 else if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32) - 1, (pC->yPos / 32)))) {
					 // pC->move(2);
					 moveFrame = 0;
					 moveDirection = 2;
					 score--;
				 }
				 else {
					 //you tried to move, but you cant
					 pC->rotate(2);
				 }
			 }
			 
			  if (e->KeyData == Keys::Right) {
				 //if you can move to the right sided tile
				  if (nL->Collide(pC->xPos + 32, pC->yPos)) {
					  PlayerHit();
				  }
			  else if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32) + 1, (pC->yPos / 32)))) {
					 // pC->move(1);
					 moveFrame = 0;
					 moveDirection = 1;
					 score--;
				 }
				 else {
					 //You tried to move but you cant
					 pC->rotate(1);

				 }
			 }
			 
			  if (e->KeyData == Keys::Up) {
				  if (nL->Collide(pC->xPos, pC->yPos - 32)) {
					  PlayerHit();
				  }
				 //If you can move to the up sided tile
				  else if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32), (pC->yPos / 32) - 1))) {
					 // pC->move(3);
					 moveFrame = 0;
					 moveDirection = 3;
					 score--;
				 }
				 else {
					 //You cant move, but tried to
					 pC->rotate(3);
				 }
			 }
			 if (e->KeyData == Keys::Down) {
				 //If you can move to the down sided tile
				 if (nL->Collide(pC->xPos , pC->yPos +32)) {
					 PlayerHit();
				 }
				 else if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32), (pC->yPos / 32) + 1))) {
					 // pC->move(0);
					 moveFrame = 0;
					 moveDirection = 0;
					 score--;
				 }

				 else {
					 //You can move but tried to
					 pC->rotate(0);
				 }

			 }
			 if (e->KeyData == Keys::Space) {
				 score--;
			 }
			 //After Moving, Pick up Items
			 pC->Pickup(iL);
			 //Check after picking up items if you lose
			 if (score == 0) {
				 Lose();
			 }
			 //STOPS SYSTEM ALERTS
			 e->Handled = true;
			 e->SuppressKeyPress = true;
		 }
	 }

 }
