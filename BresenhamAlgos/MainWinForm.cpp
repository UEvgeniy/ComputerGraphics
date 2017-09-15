#include "MainWinForm.h"
#include <Windows.h>
#include "Bresenham.h"
#include "AboutForm.h"

using namespace BresenhamAlgos; 

// main
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainWinForm);
	return 0;
}

// Constructor
inline BresenhamAlgos::MainWinForm::MainWinForm(void)
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

	// Default selection
	lineItem->PerformClick();
}

/// <summary>
/// Clean up any resources being used.
/// </summary>
inline BresenhamAlgos::MainWinForm::~MainWinForm()
{
	if (components)
	{
		delete components;
	}
}

// PictureBox is clicked
System::Void BresenhamAlgos::MainWinForm::pictureBox_MouseClick(System::Object ^ sender, MouseEventArgs ^ e)
{
	Graphics^ gr = Graphics::FromImage(bm);
	Brush^ br = gcnew SolidBrush(Color::Black);

	// todo draw dot 
	gr->FillRectangle(br, e->Location.X, e->Location.Y, 4, 4);

	points[currentClicks] = Point(e->Location.X, e->Location.Y);

	if (++currentClicks == maximumClicks) {
		currentClicks = 0;
		List<pair>^ mustDraw;

		if (lineItem->Checked) {
			mustDraw = Bresenham::buildLine(points[0].X, points[0].Y, points[1].X, points[1].Y);
		}
		else if (circleItem->Checked) {
			mustDraw = Bresenham::buildCircle(points[0].X, points[0].Y, points[1].X, points[1].Y);
		}
		else if (ellipseItem->Checked) {
			mustDraw = Bresenham::buildEllipse(points[0].X, points[0].Y, 
				(int)numericWidth->Value, (int)numericHeight->Value);
		}

		// Draw all points from list
		for (int i = 0; i < mustDraw->Count; i++) {
			pair p = mustDraw[i];
			gr->FillRectangle(br, p[0], p[1], 1, 1);
		}
	}

	delete gr;
	pictureBox->Refresh();
}

// Select line

inline System::Void BresenhamAlgos::MainWinForm::lineItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged((ToolStripMenuItem^)sender, 2);
}

// Select circle

inline System::Void BresenhamAlgos::MainWinForm::circleItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged((ToolStripMenuItem^)sender, 2);
}

// Select ellipse

inline System::Void BresenhamAlgos::MainWinForm::ellipseItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged((ToolStripMenuItem^)sender, 1);

}

// Universal method for changing checked property

inline void BresenhamAlgos::MainWinForm::itemChanged(ToolStripMenuItem ^ item, int clicksToBuild) {
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

	groupBox->Visible = ellipseItem->Checked;

}

inline System::Void BresenhamAlgos::MainWinForm::aboutItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	AboutForm^ a = gcnew AboutForm();
	a->ShowDialog();
}

inline System::Void BresenhamAlgos::MainWinForm::clearItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	Graphics^ gr = Graphics::FromImage(bm);

	currentClicks = 0;
	gr->Clear(pictureBox->BackColor);

	delete gr;
	pictureBox->Refresh();
}


void drawdot() {
	// todo 
}
