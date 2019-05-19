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
	private: System::Windows::Forms::Label^  seedShow;






	private: System::Windows::Forms::Label^  difficultyShow;

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
			System::Windows::Forms::Label^  beginLabel;
			this->gameTitle = (gcnew System::Windows::Forms::Label());
			this->difficultyLabel = (gcnew System::Windows::Forms::Label());
			this->seedLabel = (gcnew System::Windows::Forms::Label());
			this->classLabel = (gcnew System::Windows::Forms::Label());
			this->classShow = (gcnew System::Windows::Forms::Label());
			this->seedShow = (gcnew System::Windows::Forms::Label());
			this->difficultyShow = (gcnew System::Windows::Forms::Label());
			beginLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// beginLabel
			// 
			beginLabel->AutoSize = true;
			beginLabel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(44)));
			beginLabel->Cursor = System::Windows::Forms::Cursors::Default;
			beginLabel->Font = (gcnew System::Drawing::Font(L"MV Boli", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			beginLabel->ForeColor = System::Drawing::Color::Silver;
			beginLabel->Location = System::Drawing::Point(294, 467);
			beginLabel->Name = L"beginLabel";
			beginLabel->Size = System::Drawing::Size(192, 85);
			beginLabel->TabIndex = 4;
			beginLabel->Text = L"Begin";
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
			this->classShow->Location = System::Drawing::Point(500, 213);
			this->classShow->Name = L"classShow";
			this->classShow->Size = System::Drawing::Size(171, 49);
			this->classShow->TabIndex = 5;
			this->classShow->Text = L"Engineer";
			this->classShow->Click += gcnew System::EventHandler(this, &GameWindow::classShow_Click);
			// 
			// seedShow
			// 
			this->seedShow->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->seedShow->AutoSize = true;
			this->seedShow->Font = (gcnew System::Drawing::Font(L"MV Boli", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->seedShow->ForeColor = System::Drawing::Color::Silver;
			this->seedShow->Location = System::Drawing::Point(500, 296);
			this->seedShow->Name = L"seedShow";
			this->seedShow->Size = System::Drawing::Size(193, 49);
			this->seedShow->TabIndex = 6;
			this->seedShow->Text = L"         ";
			// 
			// difficultyShow
			// 
			this->difficultyShow->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->difficultyShow->AutoSize = true;
			this->difficultyShow->Font = (gcnew System::Drawing::Font(L"MV Boli", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->difficultyShow->ForeColor = System::Drawing::Color::Silver;
			this->difficultyShow->Location = System::Drawing::Point(500, 372);
			this->difficultyShow->Name = L"difficultyShow";
			this->difficultyShow->Size = System::Drawing::Size(101, 49);
			this->difficultyShow->TabIndex = 7;
			this->difficultyShow->Text = L"Easy";
			// 
			// GameWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(22)), static_cast<System::Int32>(static_cast<System::Byte>(22)),
				static_cast<System::Int32>(static_cast<System::Byte>(22)));
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->difficultyShow);
			this->Controls->Add(this->seedShow);
			this->Controls->Add(this->classShow);
			this->Controls->Add(beginLabel);
			this->Controls->Add(this->classLabel);
			this->Controls->Add(this->seedLabel);
			this->Controls->Add(this->difficultyLabel);
			this->Controls->Add(this->gameTitle);
			this->Name = L"GameWindow";
			this->Text = L"GameWindow";
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
};
}
