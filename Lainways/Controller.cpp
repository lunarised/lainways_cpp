#include "Controller.h"
#include <cstdlib> 


Controller::Controller()
{
}
void Controller::seedGen(String^ inpString) {
	inpString = inpString->ToLower();
	int n = 0;
	for (int i = 0; i < inpString->Length; i++) {
		int ab = inpString[i];
		if (ab == 32) {
			ab = 96;
		}
		n += (ab - 96) *((i + 1) * 27);
	}
	n %= 716559;
	srand(n);
}

String^ Controller::genName(){
	String^ b;
	int f = rand();
	b = f.ToString();
	return b;
}