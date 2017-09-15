#pragma once

namespace BresenhamAlgos {

	using namespace System;
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
		System::Windows::Forms::MenuStrip^			menuStrip;
		System::Windows::Forms::ToolStripMenuItem^  fieldItem;
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
#pragma endregion

	private:
		Bitmap^ bm;
		array<Point>^ points;
		List<ToolStripMenuItem^>^ items;
		int maximumClicks; // number of clicks required on pictureBox for drawing shape
		int currentClicks; // current number of clicks

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWinForm::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fieldItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circleItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ellipseItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox = (gcnew System::Windows::Forms::GroupBox());
			this->labelW = (gcnew System::Windows::Forms::Label());
			this->labelH = (gcnew System::Windows::Forms::Label());
			this->numericWidth = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericHeight = (gcnew System::Windows::Forms::NumericUpDown());
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
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->fieldItem, this->helpItem });
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuStrip->Size = System::Drawing::Size(771, 33);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// fieldItem
			// 
			this->fieldItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->addItem, this->clearItem });
			this->fieldItem->Name = L"fieldItem";
			this->fieldItem->Size = System::Drawing::Size(54, 29);
			this->fieldItem->Text = L"Edit";
			// 
			// addItem
			// 
			this->addItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->lineItem, this->circleItem,
					this->ellipseItem
			});
			this->addItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addItem.Image")));
			this->addItem->Name = L"addItem";
			this->addItem->Size = System::Drawing::Size(175, 30);
			this->addItem->Text = L"Add";
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
			// clearItem
			// 
			this->clearItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"clearItem.Image")));
			this->clearItem->Name = L"clearItem";
			this->clearItem->Size = System::Drawing::Size(175, 30);
			this->clearItem->Text = L"Clear filed";
			this->clearItem->Click += gcnew System::EventHandler(this, &MainWinForm::clearItem_Click);
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
			this->aboutItem->Size = System::Drawing::Size(211, 30);
			this->aboutItem->Text = L"About...";
			this->aboutItem->Click += gcnew System::EventHandler(this, &MainWinForm::aboutItem_Click);
			// 
			// pictureBox
			// 
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Location = System::Drawing::Point(0, 33);
			this->pictureBox->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(771, 410);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox->TabIndex = 1;
			this->pictureBox->TabStop = false;
			this->pictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainWinForm::pictureBox_MouseClick);
			// 
			// groupBox
			// 
			this->groupBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox->Controls->Add(this->labelW);
			this->groupBox->Controls->Add(this->labelH);
			this->groupBox->Controls->Add(this->numericWidth);
			this->groupBox->Controls->Add(this->numericHeight);
			this->groupBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox->Location = System::Drawing::Point(420, 367);
			this->groupBox->Name = L"groupBox";
			this->groupBox->Size = System::Drawing::Size(338, 63);
			this->groupBox->TabIndex = 2;
			this->groupBox->TabStop = false;
			this->groupBox->Text = L"Ellipse properties";
			// 
			// labelW
			// 
			this->labelW->AutoSize = true;
			this->labelW->Location = System::Drawing::Point(196, 27);
			this->labelW->Name = L"labelW";
			this->labelW->Size = System::Drawing::Size(54, 20);
			this->labelW->TabIndex = 6;
			this->labelW->Text = L"Width:";
			// 
			// labelH
			// 
			this->labelH->AutoSize = true;
			this->labelH->Location = System::Drawing::Point(6, 27);
			this->labelH->Name = L"labelH";
			this->labelH->Size = System::Drawing::Size(60, 20);
			this->labelH->TabIndex = 5;
			this->labelH->Text = L"Height:";
			// 
			// numericWidth
			// 
			this->numericWidth->Location = System::Drawing::Point(256, 25);
			this->numericWidth->Name = L"numericWidth";
			this->numericWidth->Size = System::Drawing::Size(76, 26);
			this->numericWidth->TabIndex = 4;
			this->numericWidth->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			// 
			// numericHeight
			// 
			this->numericHeight->Location = System::Drawing::Point(72, 25);
			this->numericHeight->Name = L"numericHeight";
			this->numericHeight->Size = System::Drawing::Size(62, 26);
			this->numericHeight->TabIndex = 3;
			this->numericHeight->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 0 });
			// 
			// MainWinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(771, 443);
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

			// Universal method for changing checked property
			void itemChanged(ToolStripMenuItem^ item, int clicksToBuild);

private: System::Void aboutItem_Click(System::Object^  sender, System::EventArgs^  e);
};
}