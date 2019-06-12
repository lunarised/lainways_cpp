#include "GameEngine.h"
#include <cstdlib> 
#include <time.h>

GameEngine::GameEngine(Graphics^ _canvas)
{
	canvas = _canvas;
	fill = gcnew SolidBrush(Color::Aqua);

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
	 pC->updateFrame();
	 pC->discover(tm, NCOLS, NROWS);
	 vP->moveRelativeToPlayer(pC->xPos, pC->yPos);
	 vP->ViewportDraw();
	 pC->forceDraw(400, 304);
	 

 }
 void GameEngine::TileInit() {
	 Tile^ cobble = gcnew Tile(gcnew Bitmap("cobble.bmp"), true);
	 Tile^ flower = gcnew Tile(gcnew Bitmap("flower.bmp"), false);
	 Tile^ grass = gcnew Tile(gcnew Bitmap("grass.bmp"), true);
	 ts = gcnew TileSet(4);
	 ts->SetTileArrayEntry(0, cobble);
	 ts->SetTileArrayEntry(1, flower);
	 ts->SetTileArrayEntry(2, grass);
 }
 void GameEngine::MapGen() {
	 tm = gcnew TileMap(ts, canvas, NROWS, NCOLS);
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
 void GameEngine::Keys(KeyEventArgs^ e) {
	 if (e->KeyData == Keys::A) {
		 if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32) - 1, (pC->yPos / 32)))) {
			 pC->move(2);
		 }
		 else {
			 pC->rotate(2);
		 }
	 }
	 if (e->KeyData == Keys::D) {
		 if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32) + 1, (pC->yPos / 32)))) {
			 pC->move(1);
		 }
		 else {
			 pC->rotate(1);
		 }
	 }
	 if (e->KeyData == Keys::W) {
		 if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32), (pC->yPos / 32) - 1))) {
			 pC->move(3);
		 }
		 else {
			 pC->rotate(3);
		 }
	 }
	 if (e->KeyData == Keys::S) {
		 if (ts->GetWalkable(tm->GetMapEntry((pC->xPos / 32), (pC->yPos / 32) + 1))) {
			 pC->move(0);
		 }
		 else {
			 pC->rotate(0);
		 }
	 }

 }
