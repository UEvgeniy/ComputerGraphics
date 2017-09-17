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
	Pen^ pen = gcnew Pen(Color::Red);

	draw_dot(gr, e->Location.X, e->Location.Y, 2);

	points[currentClicks] = Point(e->Location.X, e->Location.Y);

	// If all required dots added to pictureBox, then build shape
	if (++currentClicks == maximumClicks) {
		currentClicks = 0;
		draw_shapes(gr, pen);
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
// Select about
inline System::Void BresenhamAlgos::MainWinForm::aboutItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	AboutForm^ a = gcnew AboutForm();
	a->ShowDialog();
}

// Select clear
inline System::Void BresenhamAlgos::MainWinForm::clearItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	Graphics^ gr = Graphics::FromImage(bm);

	currentClicks = 0;
	gr->Clear(pictureBox->BackColor);

	delete gr;
	pictureBox->Refresh();
}

// Universal method for changing checked property
inline void BresenhamAlgos::MainWinForm::itemChanged(ToolStripMenuItem ^ item, int clicksToBuild) {

	if (item->Checked) {
		return;
	}

	currentClicks = 0;

	// different shapes required different number of clicks for drawing
	maximumClicks = clicksToBuild;

	// update checked state of items
	for (int i = 0; i < items->Count; i++) {
		items[i]->Checked = false;
	}
	item->Checked = true;

	// if ellipse selected make groupBox visible
	groupBox->Visible = ellipseItem->Checked;
}

int BresenhamAlgos::MainWinForm::length(Point ^ a, Point ^ b)
{
	int len = (int)Math::Sqrt(Math::Pow(a->X - b->X, 2) + Math::Pow(a->Y - b->Y, 2));
	return len;
}

// Draw dot (rectangle)
inline void BresenhamAlgos::MainWinForm::draw_dot(Graphics ^ gr, int x, int y, int size) {
	gr->FillRectangle(gcnew SolidBrush(Color::Black), x - (size / 2), y - (size / 2), size, size);
}

inline void BresenhamAlgos::MainWinForm::draw_shapes(Graphics ^ gr, Pen ^ pen)
{
	List<pair>^ drawn_dots;

	// variable just to make code more readable
	Point^ p1 = points[0];
	Point^ p2 = points[1];

	if (lineItem->Checked) {
		gr->DrawLine(pen, 
			p1->X, p1->Y, 
			p2->X, p2->Y);
		drawn_dots = Bresenham::buildLine(p1->X, p1->Y, p2->X, p2->Y);
	}
	else if (circleItem->Checked) {
		int rad = length(p1, p2);

		gr->DrawEllipse(pen, 
			p1->X - rad, p1->Y - rad, 
			2 * rad, 2 * rad);
		drawn_dots = Bresenham::buildCircle(p1->X, p1->Y, p2->X, p2->Y);
	}
	else if (ellipseItem->Checked) {

		int width = (int)numericWidth->Value;
		int height = (int)numericHeight->Value;

		gr->DrawEllipse(pen, 
			p1->X - width, p1->Y - height,
			width * 2, height * 2);
		drawn_dots = Bresenham::buildEllipse(p1->X, p1->Y, width, height);
	}

	// Draw all points from list
	for (int i = 0; i < drawn_dots->Count; i++) {
		pair p = drawn_dots[i];
		draw_dot(gr, p[0], p[1], 1);
		
	}
}

// Button exchanging height and width values
System::Void BresenhamAlgos::MainWinForm::exchangeButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Decimal tmp = numericHeight->Value;
	numericHeight->Value = numericWidth->Value;
	numericWidth->Value = tmp;

}


