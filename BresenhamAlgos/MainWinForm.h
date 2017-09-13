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
		MainWinForm(void)
		{
			InitializeComponent();

			// Bitmap
			bm = gcnew Bitmap(pictureBox->Width, pictureBox->Height);
			pictureBox->Image = bm;

			// Points clicked on the picture box
			points = gcnew array<Point>(3);

			// Group of toolMenuItems (only one can be checked)
			items = gcnew List<ToolStripMenuItem^>();
			items->Add(lineItem);
			items->Add(circleItem);
			items->Add(ellipseItem);

			lineItem->PerformClick();

			// todo replace
			//Graphics^ gr = Graphics::FromImage(bm);
			//gr->Clear(Color::Aqua);
			//gr->DrawLine(Pens::Black, 20, 20, 40, 50);
			//delete gr;
			//pictureBox->Refresh();

			//
			//TODO: Add the constructor code here
			//

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWinForm()
		{
			if (components)
			{
				delete components;
			}
		}

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
		System::Windows::Forms::PictureBox^			pictureBox;

	private:
		Bitmap^ bm;
		array<Point>^ points;
		List<ToolStripMenuItem^>^ items;
		int maximumClicks;
		int currentClicks;


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
			this->menuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
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
			this->addItem->Name = L"addItem";
			this->addItem->Size = System::Drawing::Size(211, 30);
			this->addItem->Text = L"Add";
			// 
			// lineItem
			// 
			this->lineItem->Name = L"lineItem";
			this->lineItem->Size = System::Drawing::Size(211, 30);
			this->lineItem->Text = L"Line";
			this->lineItem->Click += gcnew System::EventHandler(this, &MainWinForm::lineItem_Click);
			// 
			// circleItem
			// 
			this->circleItem->Name = L"circleItem";
			this->circleItem->Size = System::Drawing::Size(211, 30);
			this->circleItem->Text = L"Circle";
			this->circleItem->Click += gcnew System::EventHandler(this, &MainWinForm::circleItem_Click);
			// 
			// ellipseItem
			// 
			this->ellipseItem->Name = L"ellipseItem";
			this->ellipseItem->Size = System::Drawing::Size(211, 30);
			this->ellipseItem->Text = L"Ellipse";
			this->ellipseItem->Click += gcnew System::EventHandler(this, &MainWinForm::ellipseItem_Click);
			// 
			// clearItem
			// 
			this->clearItem->Name = L"clearItem";
			this->clearItem->Size = System::Drawing::Size(211, 30);
			this->clearItem->Text = L"Clear";
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
			this->aboutItem->Name = L"aboutItem";
			this->aboutItem->Size = System::Drawing::Size(159, 30);
			this->aboutItem->Text = L"About...";
			// 
			// pictureBox
			// 
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Location = System::Drawing::Point(0, 33);
			this->pictureBox->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(771, 397);
			this->pictureBox->TabIndex = 1;
			this->pictureBox->TabStop = false;
			this->pictureBox->Click += gcnew System::EventHandler(this, &MainWinForm::pictureBox_Click);
			// 
			// MainWinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(771, 430);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->menuStrip);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MainMenuStrip = this->menuStrip;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MainWinForm";
			this->Text = L"BresenhamAlgos";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Click on the picture box
		private: 
			System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {

			}

			// Select line
			System::Void lineItem_Click(System::Object^  sender, System::EventArgs^  e) {
				itemChanged((ToolStripMenuItem^)sender, 2);
			}
			// Select circle
			System::Void circleItem_Click(System::Object^  sender, System::EventArgs^  e) {
				itemChanged((ToolStripMenuItem^)sender, 2);
			}
			// Select ellipse
			System::Void ellipseItem_Click(System::Object^  sender, System::EventArgs^  e) {
				itemChanged((ToolStripMenuItem^)sender, 3);
			}

			// Universal method for changing checked property
			void itemChanged(ToolStripMenuItem^ item, int clicksToBuild) {
				currentClicks = 0;
				
				if (item->Checked) {
					return;
				}

				maximumClicks = clicksToBuild;

				// todo change
				for (int i = 0; i < items->Count; i++) {
					items[i]->Checked = false;
				}

				item->Checked = true;

			}

			///////////////////////////////////////////////////////////////////////////
};
}