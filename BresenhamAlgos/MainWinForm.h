#pragma once

namespace BresenhamAlgos {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWinForm
	/// </summary>
	public ref class MainWinForm : public System::Windows::Forms::Form
	{
	public:
		MainWinForm(void)
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
		~MainWinForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  fieldItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpItem;

	protected:






	private: System::Windows::Forms::ToolStripMenuItem^  addItem;
	private: System::Windows::Forms::ToolStripMenuItem^  lineItem;
	private: System::Windows::Forms::ToolStripMenuItem^  circleItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ellipseItem;





	private: System::Windows::Forms::ToolStripMenuItem^  clearItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutItem;


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
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fieldItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circleItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ellipseItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->fieldItem, this->helpItem });
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(578, 33);
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
			// helpItem
			// 
			this->helpItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutItem });
			this->helpItem->Name = L"helpItem";
			this->helpItem->Size = System::Drawing::Size(61, 29);
			this->helpItem->Text = L"Help";
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
			this->lineItem->Checked = true;
			this->lineItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->lineItem->Name = L"lineItem";
			this->lineItem->Size = System::Drawing::Size(211, 30);
			this->lineItem->Text = L"Line";
			// 
			// circleItem
			// 
			this->circleItem->Name = L"circleItem";
			this->circleItem->Size = System::Drawing::Size(211, 30);
			this->circleItem->Text = L"Circle";
			// 
			// ellipseItem
			// 
			this->ellipseItem->Name = L"ellipseItem";
			this->ellipseItem->Size = System::Drawing::Size(211, 30);
			this->ellipseItem->Text = L"Ellipse";
			// 
			// clearItem
			// 
			this->clearItem->Name = L"clearItem";
			this->clearItem->Size = System::Drawing::Size(211, 30);
			this->clearItem->Text = L"Clear";
			// 
			// aboutItem
			// 
			this->aboutItem->Name = L"aboutItem";
			this->aboutItem->Size = System::Drawing::Size(211, 30);
			this->aboutItem->Text = L"About...";
			// 
			// MainWinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(578, 344);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"MainWinForm";
			this->Text = L"BresenhamAlgos";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}
