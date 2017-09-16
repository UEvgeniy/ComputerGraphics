#include "AboutForm.h"

// Constructor
inline BresenhamAlgos::AboutForm::AboutForm(void)
{
	InitializeComponent();
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

// Contact button clicked
inline System::Void BresenhamAlgos::AboutForm::button_Click(System::Object ^ sender, System::EventArgs ^ e) {
	// todo mailto
}
