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
	{
		List<pair>^ drawn_dots;

		if (lineItem->Checked) {
			gr->DrawLine(pen, points[0].X, points[0].Y, points[1].X, points[1].Y);
			drawn_dots = Bresenham::buildLine(points[0].X, points[0].Y, points[1].X, points[1].Y);
		}
		else if (circleItem->Checked) {
			int rad = length(points[0], points[1]);
			gr->DrawEllipse(pen, points[0].X - rad, points[0].Y - rad, 2 * rad, 2 * rad);
			drawn_dots = Bresenham::buildCircle(points[0].X, points[0].Y, points[1].X, points[1].Y);
		}
		else if (ellipseItem->Checked) {
			gr->DrawEllipse(pen, points[0].X - (int)numericWidth->Value, points[0].Y - (int)numericHeight->Value,
				(int)numericWidth->Value * 2, (int)numericHeight->Value * 2);
			drawn_dots = Bresenham::buildEllipse(points[0].X, points[0].Y,
				(int)numericWidth->Value, (int)numericHeight->Value);
		}

		// Draw all points from list
		for (int i = 0; i < drawn_dots->Count; i++) {
			pair p = drawn_dots[i];
			draw_dot(gr, p[0], p[1], 1);
		}
	}
}


