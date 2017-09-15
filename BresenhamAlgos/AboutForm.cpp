#include "AboutForm.h"

inline BresenhamAlgos::AboutForm::AboutForm(void)
{
	InitializeComponent();
	//
	//TODO: Add the constructor code here
	//
}

/// <summary>
/// Clean up any resources being used.
/// </summary>

inline BresenhamAlgos::AboutForm::~AboutForm()
{
	if (components)
	{
		delete components;
	}
}

inline System::Void BresenhamAlgos::AboutForm::button_Click(System::Object ^ sender, System::EventArgs ^ e) {
	// todo
}
