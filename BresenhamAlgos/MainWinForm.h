#pragma once
#include "GShape.h"
// Sem 1. Bresenham Algos. 
// Sem 2. Filling, clipping.
// Made by Evgeniy Urnyshev. Moscow, 2017.
namespace BresenhamAlgos {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for MainWinForm
	/// </summary>
	public ref class MainWinForm : public System::Windows::Forms::Form {

	public:
		MainWinForm(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWinForm();

#pragma region Fields - Controls

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
 
		System::Windows::Forms::MenuStrip^			menuStrip;
		System::Windows::Forms::ToolStripMenuItem^  graphicsItem;

		System::Windows::Forms::ToolStripMenuItem^  helpItem;
		System::Windows::Forms::ToolStripMenuItem^  addItem;
		System::Windows::Forms::ToolStripMenuItem^  lineItem;
		System::Windows::Forms::ToolStripMenuItem^  circleItem;
		System::Windows::Forms::ToolStripMenuItem^  ellipseItem;
		System::Windows::Forms::ToolStripMenuItem^  clearItem;
		System::Windows::Forms::ToolStripMenuItem^  aboutItem;

		System::Windows::Forms::PictureBox^		pictureBox;
		System::Windows::Forms::GroupBox^		groupBox;
		System::Windows::Forms::Label^			labelW;
		System::Windows::Forms::Label^			labelH;
		System::Windows::Forms::NumericUpDown^	numericWidth;
		System::Windows::Forms::NumericUpDown^	numericHeight;

		System::Windows::Forms::Button^  exchangeButton;
		System::Windows::Forms::ToolStripMenuItem^  fileItem;
		System::Windows::Forms::ToolStripMenuItem^  openItem;
		System::Windows::Forms::ToolStripMenuItem^  saveItem;
		System::Windows::Forms::ToolStripMenuItem^  fillItem;
		System::Windows::Forms::ToolStripMenuItem^  settingsItem;
		System::Windows::Forms::ToolStripMenuItem^  colorItem;
		System::Windows::Forms::ColorDialog^  colorDialog;
#pragma endregion

	private:

		Bitmap^ bm;
		array<Point^>^ points;
		List<ToolStripMenuItem^>^ items;
		List<GShape^>^ shapes;
		int maximumClicks; // number of clicks required on pictureBox for drawing shape
	private: System::Windows::Forms::SaveFileDialog^  saveDialog;
			 int currentClicks; // current number of clicks



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWinForm::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->graphicsItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circleItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ellipseItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fillItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->settingsItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox = (gcnew System::Windows::Forms::GroupBox());
			this->exchangeButton = (gcnew System::Windows::Forms::Button());
			this->labelW = (gcnew System::Windows::Forms::Label());
			this->labelH = (gcnew System::Windows::Forms::Label());
			this->numericWidth = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericHeight = (gcnew System::Windows::Forms::NumericUpDown());
			this->colorDialog = (gcnew System::Windows::Forms::ColorDialog());
			this->saveDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->groupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericWidth))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericHeight))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileItem, this->graphicsItem,
					this->settingsItem, this->helpItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuStrip->Size = System::Drawing::Size(878, 33);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// fileItem
			// 
			this->fileItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->openItem, this->saveItem });
			this->fileItem->Name = L"fileItem";
			this->fileItem->Size = System::Drawing::Size(50, 29);
			this->fileItem->Text = L"File";
			// 
			// openItem
			// 
			this->openItem->Name = L"openItem";
			this->openItem->Size = System::Drawing::Size(153, 30);
			this->openItem->Text = L"Open...";
			// 
			// saveItem
			// 
			this->saveItem->Name = L"saveItem";
			this->saveItem->Size = System::Drawing::Size(153, 30);
			this->saveItem->Text = L"Save...";
			this->saveItem->Click += gcnew System::EventHandler(this, &MainWinForm::saveItem_Click);
			// 
			// graphicsItem
			// 
			this->graphicsItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->addItem,
					this->fillItem, this->clearItem
			});
			this->graphicsItem->Name = L"graphicsItem";
			this->graphicsItem->Size = System::Drawing::Size(92, 29);
			this->graphicsItem->Text = L"Graphics";
			// 
			// addItem
			// 
			this->addItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->lineItem, this->circleItem,
					this->ellipseItem
			});
			this->addItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addItem.Image")));
			this->addItem->Name = L"addItem";
			this->addItem->Size = System::Drawing::Size(183, 30);
			this->addItem->Text = L"Add shape";
			// 
			// lineItem
			// 
			this->lineItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lineItem.Image")));
			this->lineItem->Name = L"lineItem";
			this->lineItem->Size = System::Drawing::Size(146, 30);
			this->lineItem->Text = L"Line";
			this->lineItem->Click += gcnew System::EventHandler(this, &MainWinForm::lineItem_Click);
			// 
			// circleItem
			// 
			this->circleItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"circleItem.Image")));
			this->circleItem->Name = L"circleItem";
			this->circleItem->Size = System::Drawing::Size(146, 30);
			this->circleItem->Text = L"Circle";
			this->circleItem->Click += gcnew System::EventHandler(this, &MainWinForm::circleItem_Click);
			// 
			// ellipseItem
			// 
			this->ellipseItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ellipseItem.Image")));
			this->ellipseItem->Name = L"ellipseItem";
			this->ellipseItem->Size = System::Drawing::Size(146, 30);
			this->ellipseItem->Text = L"Ellipse";
			this->ellipseItem->Click += gcnew System::EventHandler(this, &MainWinForm::ellipseItem_Click);
			// 
			// fillItem
			// 
			this->fillItem->Name = L"fillItem";
			this->fillItem->Size = System::Drawing::Size(183, 30);
			this->fillItem->Text = L"Fill";
			// 
			// clearItem
			// 
			this->clearItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"clearItem.Image")));
			this->clearItem->Name = L"clearItem";
			this->clearItem->Size = System::Drawing::Size(183, 30);
			this->clearItem->Text = L"Clear filed";
			this->clearItem->Click += gcnew System::EventHandler(this, &MainWinForm::clearItem_Click);
			// 
			// settingsItem
			// 
			this->settingsItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->colorItem });
			this->settingsItem->Name = L"settingsItem";
			this->settingsItem->Size = System::Drawing::Size(88, 29);
			this->settingsItem->Text = L"Settings";
			// 
			// colorItem
			// 
			this->colorItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"colorItem.Image")));
			this->colorItem->Name = L"colorItem";
			this->colorItem->Size = System::Drawing::Size(152, 30);
			this->colorItem->Text = L"Color...";
			this->colorItem->Click += gcnew System::EventHandler(this, &MainWinForm::colorItem_Click);
			// 
			// helpItem
			// 
			this->helpItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutItem });
			this->helpItem->Name = L"helpItem";
			this->helpItem->Size = System::Drawing::Size(61, 29);
			this->helpItem->Text = L"Help";
			// 
			// aboutItem
			// 
			this->aboutItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"aboutItem.Image")));
			this->aboutItem->Name = L"aboutItem";
			this->aboutItem->Size = System::Drawing::Size(159, 30);
			this->aboutItem->Text = L"About...";
			this->aboutItem->Click += gcnew System::EventHandler(this, &MainWinForm::aboutItem_Click);
			// 
			// pictureBox
			// 
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Location = System::Drawing::Point(0, 33);
			this->pictureBox->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(878, 411);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox->TabIndex = 1;
			this->pictureBox->TabStop = false;
			this->pictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainWinForm::pictureBox_MouseClick);
			// 
			// groupBox
			// 
			this->groupBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox->Controls->Add(this->exchangeButton);
			this->groupBox->Controls->Add(this->labelW);
			this->groupBox->Controls->Add(this->labelH);
			this->groupBox->Controls->Add(this->numericWidth);
			this->groupBox->Controls->Add(this->numericHeight);
			this->groupBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox->Location = System::Drawing::Point(718, 331);
			this->groupBox->Name = L"groupBox";
			this->groupBox->Size = System::Drawing::Size(147, 106);
			this->groupBox->TabIndex = 2;
			this->groupBox->TabStop = false;
			this->groupBox->Text = L"Ellipse properties";
			// 
			// exchangeButton
			// 
			this->exchangeButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->exchangeButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"exchangeButton.Image")));
			this->exchangeButton->Location = System::Drawing::Point(25, 43);
			this->exchangeButton->Name = L"exchangeButton";
			this->exchangeButton->Size = System::Drawing::Size(39, 23);
			this->exchangeButton->TabIndex = 3;
			this->exchangeButton->UseVisualStyleBackColor = true;
			this->exchangeButton->Click += gcnew System::EventHandler(this, &MainWinForm::exchangeButton_Click);
			// 
			// labelW
			// 
			this->labelW->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->labelW->AutoSize = true;
			this->labelW->Location = System::Drawing::Point(2, 73);
			this->labelW->Name = L"labelW";
			this->labelW->Size = System::Drawing::Size(50, 20);
			this->labelW->TabIndex = 6;
			this->labelW->Text = L"Width";
			// 
			// labelH
			// 
			this->labelH->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->labelH->AutoSize = true;
			this->labelH->Location = System::Drawing::Point(2, 18);
			this->labelH->Name = L"labelH";
			this->labelH->Size = System::Drawing::Size(56, 20);
			this->labelH->TabIndex = 5;
			this->labelH->Text = L"Height";
			// 
			// numericWidth
			// 
			this->numericWidth->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->numericWidth->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericWidth->Location = System::Drawing::Point(95, 71);
			this->numericWidth->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 700, 0, 0, 0 });
			this->numericWidth->Name = L"numericWidth";
			this->numericWidth->Size = System::Drawing::Size(45, 26);
			this->numericWidth->TabIndex = 4;
			this->numericWidth->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			// 
			// numericHeight
			// 
			this->numericHeight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->numericHeight->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericHeight->Location = System::Drawing::Point(95, 16);
			this->numericHeight->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 400, 0, 0, 0 });
			this->numericHeight->Name = L"numericHeight";
			this->numericHeight->Size = System::Drawing::Size(45, 26);
			this->numericHeight->TabIndex = 3;
			this->numericHeight->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 0 });
			// 
			// saveDialog
			// 
			this->saveDialog->FileName = L"shapes";
			this->saveDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainWinForm::saveDialog_FileOk);
			// 
			// MainWinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(878, 444);
			this->Controls->Add(this->groupBox);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->menuStrip);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(900, 500);
			this->MinimumSize = System::Drawing::Size(900, 500);
			this->Name = L"MainWinForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"BresenhamAlgos";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->groupBox->ResumeLayout(false);
			this->groupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericWidth))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericHeight))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: 
		
			// Click on PictureBox
			System::Void pictureBox_MouseClick(System::Object^  sender, MouseEventArgs^  e);

			// Select line
			System::Void lineItem_Click(System::Object^  sender, System::EventArgs^  e);
			// Select circle
			System::Void circleItem_Click(System::Object^  sender, System::EventArgs^  e);
			// Select ellipse
			System::Void ellipseItem_Click(System::Object^  sender, System::EventArgs^  e);
			// Select clear field
			System::Void clearItem_Click(System::Object^  sender, System::EventArgs^  e);
			// Select about
			System::Void aboutItem_Click(System::Object^  sender, System::EventArgs^  e);

			// Universal method for changing checked property
			void itemChanged(ToolStripMenuItem^ item, int clicksToBuild);

			// Length between 2 dots
			int length(Point^ a, Point^ b);

			// Drawing dot
			void draw_dot(Graphics^ gr, int x, int y, Color col, int size);

			// Get Shape by menuItems and points
			GShape^ formShape(int depth);

			// Draw shape
			void drawShape(Graphics^ gr, GShape^ shape);



			// For ellipse height and width values changing
			System::Void exchangeButton_Click(System::Object^  sender, System::EventArgs^  e);

			// Color settings
			System::Void colorItem_Click(System::Object^  sender, System::EventArgs^  e);

	System::Void saveItem_Click(System::Object^  sender, System::EventArgs^  e) {
		saveDialog->ShowDialog();

}
	System::Void saveDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	
		StreamWriter^ sw = gcnew StreamWriter(saveDialog->FileName);

		for each (GShape^ shape in shapes)
		{
			sw->WriteLine(shape->ToString());
		}
		sw->Close();
		}
};
}