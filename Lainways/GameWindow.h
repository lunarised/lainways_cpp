#pragma once

namespace Lainways {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GameWindow
	/// </summary>
	public ref class GameWindow : public System::Windows::Forms::Form
	{
	public:
		GameWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  gameTitle;
	private: System::Windows::Forms::Label^  difficultyLabel;
	private: System::Windows::Forms::Label^  seedLabel;


	private: System::Windows::Forms::Label^  classLabel;
	private: System::Windows::Forms::Label^  classShow;







	private: System::Windows::Forms::Label^  difficultyShow;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  eNameLabel;
	private: System::Windows::Forms::Label^  scorelab;
	private: System::Windows::Forms::Label^  startlab;



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->gameTitle = (gcnew System::Windows::Forms::Label());
			this->difficultyLabel = (gcnew System::Windows::Forms::Label());
			this->seedLabel = (gcnew System::Windows::Forms::Label());
			this->classLabel = (gcnew System::Windows::Forms::Label());
			this->classShow = (gcnew System::Windows::Forms::Label());
			this->difficultyShow = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->eNameLabel = (gcnew System::Windows::Forms::Label());
			this->scorelab = (gcnew System::Windows::Forms::Label());
			this->startlab = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// gameTitle
			// 
			this->gameTitle->AutoSize = true;
			this->gameTitle->Font = (gcnew System::Drawing::Font(L"MV Boli", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gameTitle->ForeColor = System::Drawing::Color::Silver;
			this->gameTitle->Location = System::Drawing::Point(235, 21);
			this->gameTitle->Name = L"gameTitle";
			this->gameTitle->Size = System::Drawing::Size(310, 85);
			this->gameTitle->TabIndex = 0;
			this->gameTitle->Text = L"lainways_";
			// 
			// difficultyLabel
			// 
			this->difficultyLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->difficultyLabel->AutoSize = true;
			this->difficultyLabel->Font = (gcnew System::Drawing::Font(L"MV Boli", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->difficultyLabel->ForeColor = System::Drawing::Color::Silver;
			this->difficultyLabel->Location = System::Drawing::Point(12, 372);
			this->difficultyLabel->Name = L"difficultyLabel";
			this->difficultyLabel->Size = System::Drawing::Size(335, 49);
			this->difficultyLabel->TabIndex = 1;
			this->difficultyLabel->Text = L"Select Difficulty:";
			// 
			// seedLabel
			// 
			this->seedLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->seedLabel->AutoSize = true;
			this->seedLabel->Font = (gcnew System::Drawing::Font(L"MV Boli", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->seedLabel->ForeColor = System::Drawing::Color::Silver;
			this->seedLabel->Location = System::Drawing::Point(12, 296);
			this->seedLabel->Name = L"seedLabel";
			this->seedLabel->Size = System::Drawing::Size(248, 49);
			this->seedLabel->TabIndex = 2;
			this->seedLabel->Text = L"Select Seed:";
			// 
			// classLabel
			// 
			this->classLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->classLabel->AutoSize = true;
			this->classLabel->Font = (gcnew System::Drawing::Font(L"MV Boli", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->classLabel->ForeColor = System::Drawing::Color::Silver;
			this->classLabel->Location = System::Drawing::Point(12, 213);
			this->classLabel->Name = L"classLabel";
			this->classLabel->Size = System::Drawing::Size(249, 49);
			this->classLabel->TabIndex = 3;
			this->classLabel->Text = L"Select Class:";
			this->classLabel->Click += gcnew System::EventHandler(this, &GameWindow::classLabel_Click);
			// 
			// classShow
			// 
			this->classShow->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->classShow->AutoSize = true;
			this->classShow->Font = (gcnew System::Drawing::Font(L"MV Boli", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->classShow->ForeColor = System::Drawing::Color::Silver;
			this->classShow->Location = System::Drawing::Point(547, 213);
			this->classShow->Name = L"classShow";
			this->classShow->Size = System::Drawing::Size(171, 49);
			this->classShow->TabIndex = 5;
			this->classShow->Text = L"Engineer";
			this->classShow->Click += gcnew System::EventHandler(this, &GameWindow::classShow_Click);
			// 
			// difficultyShow
			// 
			this->difficultyShow->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->difficultyShow->AutoSize = true;
			this->difficultyShow->Font = (gcnew System::Drawing::Font(L"MV Boli", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->difficultyShow->ForeColor = System::Drawing::Color::Silver;
			this->difficultyShow->Location = System::Drawing::Point(609, 372);
			this->difficultyShow->Name = L"difficultyShow";
			this->difficultyShow->Size = System::Drawing::Size(101, 49);
			this->difficultyShow->TabIndex = 7;
			this->difficultyShow->Text = L"Easy";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(22)), static_cast<System::Int32>(static_cast<System::Byte>(22)),
				static_cast<System::Int32>(static_cast<System::Byte>(22)));
			this->textBox1->Font = (gcnew System::Drawing::Font(L"MV Boli", 18, System::Drawing::FontStyle::Bold));
			this->textBox1->ForeColor = System::Drawing::Color::Silver;
			this->textBox1->Location = System::Drawing::Point(329, 299);
			this->textBox1->MaxLength = 24;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(389, 46);
			this->textBox1->TabIndex = 8;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// eNameLabel
			// 
			this->eNameLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->eNameLabel->Font = (gcnew System::Drawing::Font(L"MV Boli", 20, System::Drawing::FontStyle::Bold));
			this->eNameLabel->ForeColor = System::Drawing::Color::Silver;
			this->eNameLabel->Location = System::Drawing::Point(15, 9);
			this->eNameLabel->Name = L"eNameLabel";
			this->eNameLabel->Size = System::Drawing::Size(249, 37);
			this->eNameLabel->TabIndex = 9;
			this->eNameLabel->Text = L"O";
			this->eNameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// scorelab
			// 
			this->scorelab->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->scorelab->Font = (gcnew System::Drawing::Font(L"MV Boli", 20, System::Drawing::FontStyle::Bold));
			this->scorelab->ForeColor = System::Drawing::Color::Silver;
			this->scorelab->Location = System::Drawing::Point(523, 9);
			this->scorelab->Name = L"scorelab";
			this->scorelab->Size = System::Drawing::Size(249, 37);
			this->scorelab->TabIndex = 10;
			this->scorelab->Text = L"O";
			this->scorelab->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// startlab
			// 
			this->startlab->AutoSize = true;
			this->startlab->Font = (gcnew System::Drawing::Font(L"MV Boli", 32, System::Drawing::FontStyle::Bold));
			this->startlab->ForeColor = System::Drawing::Color::Silver;
			this->startlab->Location = System::Drawing::Point(341, 480);
			this->startlab->Name = L"startlab";
			this->startlab->Size = System::Drawing::Size(131, 55);
			this->startlab->TabIndex = 11;
			this->startlab->Text = L"Begin";
			this->startlab->Click += gcnew System::EventHandler(this, &GameWindow::startlab_Click);
			// 
			// GameWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(22)), static_cast<System::Int32>(static_cast<System::Byte>(22)),
				static_cast<System::Int32>(static_cast<System::Byte>(22)));
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->startlab);
			this->Controls->Add(this->scorelab);
			this->Controls->Add(this->eNameLabel);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->difficultyShow);
			this->Controls->Add(this->classShow);
			this->Controls->Add(this->classLabel);
			this->Controls->Add(this->seedLabel);
			this->Controls->Add(this->difficultyLabel);
			this->Controls->Add(this->gameTitle);
			this->Name = L"GameWindow";
			this->Text = L"GameWindow";
			this->Load += gcnew System::EventHandler(this, &GameWindow::GameWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void classLabel_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void classShow_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void classOnClick() {

}
private: System::Void diffOnClick() {

		 }

private: System::Void GameWindow_Load(System::Object^  sender, System::EventArgs^  e) {
	menuLabel();

}
private: System::Void beginLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	gameLabel();

}

private: System::Void gameLabel() {
	scorelab->Visible = true;
	eNameLabel->Visible = true;
	classLabel->Visible = false;
	classShow->Visible = false;
	seedLabel->Visible = false;
	textBox1->Visible = false;
	gameTitle->Visible = false;
	difficultyLabel->Visible = false;
	difficultyShow->Visible = false;
	startlab->Visible = false;
}
private: System::Void menuLabel() {
	scorelab->Visible = false;
	eNameLabel->Visible = false;
	classLabel->Visible = true;
	classShow->Visible = true;
	seedLabel->Visible = true;
	textBox1->Visible = true;
	gameTitle->Visible = true;
	difficultyLabel->Visible = true;
	difficultyShow->Visible = true;
	startlab->Visible = true;
}
private: System::Void startlab_Click(System::Object^  sender, System::EventArgs^  e) {
	gameLabel();
	eNameLabel->Text = textBox1->Text;
}
};
}
