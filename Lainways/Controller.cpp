#include "Controller.h"
#include <cstdlib> 
#include <time.h>

Controller::Controller(Graphics^ _canvas)
{
	canvas = _canvas;
	
	fill = gcnew SolidBrush(Color::Aqua);
}
void Controller::seedGen(String^ inpString) {
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
 void Controller::genName(){
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
 void Controller::draw() {
	 fill->Color = Color::FromArgb(rand()%256, rand()%256, rand()%256, rand()%256);
	 canvas->FillRectangle(fill, 0, 0, 200, 400);
	 

 }