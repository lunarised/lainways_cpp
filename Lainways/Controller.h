#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
ref class Controller
{
private:
	Color^ c;

	
	Graphics^ canvas;
	SolidBrush^ fill;
public:
	Controller(Graphics^ _canvas);
	void seedGen(String^ inpString);
	void genName();
	void draw();
	property String^ seedName;
};




