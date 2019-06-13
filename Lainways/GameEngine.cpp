#include "GameEngine.h"
#include <cstdlib>   // for rand()
#include <time.h> //for initial random seed
/*Where most computation regarding game state should happen*/
GameEngine::GameEngine(Graphics^ _canvas)
{
	score = 80;
	state = 0;
	moveDirection = 0;
	moveFrame = 15;
	canvas = _canvas;
	fill = gcnew SolidBrush(Color::Aqua);
	p1 = gcnew Bitmap("p1.bmp");
	Color tC = p1->GetPixel(0, 0);
	p1->MakeTransparent();
}
void GameEngine::Lose() {

}
/*Generates a random seed using hashing from a String*/
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
	srand(n);//seed the random generator
}
/* Reads in a name from 2 files to be used for thematic reasons*/
 void GameEngine::genName(){
	srand(time(0));//set the seed to be random
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
 /*Handles drawing and some housekeeping on each timer tick*/
 void GameEngine::draw() {
	 pC->discover(tm, NCOLS, NROWS);
	 vP->moveRelativeToPlayer(pC->xPos, pC->yPos);
	 vP->ViewportDraw();
	 iL->drawItems(vP->ViewportWorldX, vP->ViewportWorldY);
	 nL->drawNPC(vP->ViewportWorldX, vP->ViewportWorldY);
	 if (pL->Collide(pC->xPos, pC->yPos)) {
		 Projectile^ hitP = pL->projAt(pC->xPos, pC->yPos);
		 score -= hitP->dmg;
		 pL->deleteProj(hitP);
	 }
	 //pL->KillDead
	 pL->drawProj(vP->ViewportWorldX, vP->ViewportWorldY);
	 pC->forceDraw(400, 304);
 } 
 /*Adds all tiles to the tileset*/
 void GameEngine::TileInit() {
	 Tile^ cobble = gcnew Tile(gcnew Bitmap("cobble.bmp"), true);
	 Tile^ flower = gcnew Tile(gcnew Bitmap("wall.bmp"), false);
	 Tile^ grass = gcnew Tile(gcnew Bitmap("floor0.bmp"), true);
	 Tile^ blank = gcnew Tile(gcnew Bitmap(32, 32), false);
	 ts = gcnew TileSet(4);
	 ts->SetTileArrayEntry(0, blank);
	 ts->SetTileArrayEntry(3, cobble);
	 ts->SetTileArrayEntry(1, flower);
	 ts->SetTileArrayEntry(2, grass);
 }
 /*Sets up collections and Generates the map*/
 void GameEngine::MapGen() {
	 tm = gcnew TileMap(ts, canvas, NROWS, NCOLS);
	 iL = gcnew ItemList(tm);
	 nL = gcnew NPCList(tm);
	 pL = gcnew ProjectileList(tm);
	 tm->GenerateMap(NROWS, NCOLS);  //BIG Function in TileMap.c
 }
 /*Handles player Initialisation*/
 void GameEngine::PlayerInit() {
	 Bitmap^ pCI = gcnew Bitmap("Player.bmp");
	 Color tC = pCI->GetPixel(0, 0);
	 pCI->MakeTransparent(tC);
	 pC = gcnew Player(canvas, pCI, 3);
 }
 /*Handles Init of the Viewport*/
 void GameEngine::ViewPortGen() {
	 vP = gcnew Viewport(0, 0, 25, 19, tm, canvas);
	 vP->ViewportDraw();
 }
 /*Generates Items and NPC's and Handels their bitmaps*/
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
				 if (rand() % 40 == 0) {//1 in 40 tiles should have a coin on them
					 iL->addItem(gcnew Item(canvas, coin, 16, 16, 1, i * 32, j * 32, 1));
				 }
				 else if (rand() % 200 == 0) {
					 nL->addNPC(gcnew NPC(canvas, camera, 32, 32, 1, i * 32, j * 32, 1,tm));
				 }
			 }
		 }
	 }

 }
/* Handles the player damaging an NPC*/
 void GameEngine::PlayerHit(int _x, int _y){
	 score--;//spent a move to damage
	 int damage = rand() % 5 + 1;//gen 1-5 damage
	 nL->npcAt(_x, _y)->health -= damage;
	 if (nL->npcAt(_x, _y)->health < 0) {
		 nL->deleteNPC(nL->npcAt(_x, _y));
		 score += 10;
	 }
 
 }
 /**Handles how to move the player gracefully */
 void GameEngine::PlayerMove() {
	 if (moveFrame != 15) { //if we expect to be moving
		 if (moveFrame == 0 || moveFrame == 14) {//leap frames for making up 32 pixels
			 pC->move(moveDirection, 3);
		 }
		 
		 else {
			 pC->move(moveDirection, 2);//move 2 pixels per frame
		 }
		 if (moveFrame == 0 || moveFrame == 8 || moveFrame == 14) {//update animation uniformly
			 pC->updateFrame();//update animation
		 }
		 moveFrame++; //move to the next frame of movement
	 }
	 else {//if we arent currently moving
		 int item = pC->Pickup(iL); //try to pick up an item
		 if (item == 1) { //if item is a coin
			 score += 40;
		 }
	 }
 }
 /** Handles what to do on Key Down Events */
 void GameEngine::Keys(KeyEventArgs^ e) {
	
	 if (state == 1) {//If in gameplay
		 e->SuppressKeyPress = true;
		 
		 if (moveFrame == 15 && score > 0) {
			 nL->genStates(pC->xPos, pC->yPos);
			 score -= nL->doActions(pC->xPos, pC->yPos);
			 //if you can spend a point to move, and you arent already moving
			 if (e->KeyData == Keys::A) {//if you can move to the left sided tile
				 if (nL->Collide(pC->xPos - 32, pC->yPos)) {
					 pC->rotate(2);
					 PlayerHit(pC->xPos - 32, pC->yPos);
				 }
				 else if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32) - 1, (pC->yPos / 32)))) {
					 moveFrame = 0;
					 moveDirection = 2;
					 score--;
				 }
				 else {//you tried to move, but you cant
					 pC->rotate(2);  
				 }
			 }
			  if (e->KeyData == Keys::D) {
				 
				  if (nL->Collide(pC->xPos + 32, pC->yPos)) { //if theres a monster on it
					  pC->rotate(1);
					  PlayerHit(pC->xPos + 32, pC->yPos);
				  }
			  else if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32) + 1, (pC->yPos / 32)))) { //if walkable
					 moveFrame = 0;
					 moveDirection = 1;
					 score--;
				 }
				 else { //You tried to move but you cant
					 pC->rotate(1);
				 }
			 }
			  if (e->KeyData == Keys::W) {
				  if (nL->Collide(pC->xPos, pC->yPos - 32)) {//if theres a monster on it
					  pC->rotate(3);
					  PlayerHit(pC->xPos, pC->yPos - 32);
				  }
				 
				  else if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32), (pC->yPos / 32) - 1))) {//if walkable
					 moveFrame = 0;
					 moveDirection = 3;
					 score--;
				 }
				 else { //You cant move, but tried to
					 pC->rotate(3);
				 }
			 }
			 if (e->KeyData == Keys::S) {
				 
				 if (nL->Collide(pC->xPos , pC->yPos +32)) {//if theres a mob on the tile
					 PlayerHit(pC->xPos, pC->yPos + 32);
					 pC->rotate(0);
				 }
				 else if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32), (pC->yPos / 32) + 1))) {//if tiles walkable
					 moveFrame = 0;
					 moveDirection = 0;
					 score--;
				 }
				 else {//You can move but tried to
					 pC->rotate(0);
				 }
			 }
			 

			 //Check after picking up items if you lose
			 
		
			if (e->KeyData == Keys::Space) {//Skip turn
				score--;
				pL->addProj(gcnew Projectile(canvas, p1, 16, 16, 1, pC->xPos, pC->yPos, 1, 1, pC->direction));
			}
			 if (score == 0) {
				 Lose();
			 }

			
			 pL->moveProj();
			 
			 
			
		 }
	 }

 }
