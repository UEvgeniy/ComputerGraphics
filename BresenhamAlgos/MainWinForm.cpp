#include <Windows.h>

#include "MainWinForm.h"
#include "Bresenham.h"
#include "AboutForm.h"

#include "GLine.h"
#include"GEllipse.h"
#include "GCircle.h"
#include "GShapeParser.h"
#include "StrokeFill.h"


using namespace BresenhamAlgos; 

// main
[STAThread]
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

	// Drawed shapes
	shapes = gcnew List<GShape^>();

	// Points clicked on the picture box
	points = gcnew array<Point^>(3);

	// Group of toolMenuItems (only one can be checked)
	items = gcnew List<ToolStripMenuItem^>();
	items->Add(lineItem);
	items->Add(circleItem);
	items->Add(ellipseItem);
	items->Add(strokeFillItem);

	// Default selection
	lineItem->PerformClick();
	labelH->Text = "Height (max " + numericHeight->Maximum +"):";
	labelW->Text = "Width (max " + numericWidth->Maximum + "):";

	// Save Dialog
	saveDialog->DefaultExt = "gr";
	saveDialog->Filter = "Graphics Files (*.gr)|*.gr";
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

// PictureBox is clicked (left and right)
inline System::Void BresenhamAlgos::MainWinForm::pictureBox_MouseClick(System::Object ^ sender, MouseEventArgs ^ e)
{

	Graphics^ gr = Graphics::FromImage(bm);
	//draw_dot(gr, e->Location.X, e->Location.Y, colorDialog->Color, 2);

	points[currentClicks] = Point(e->Location.X, e->Location.Y);

	// If all required dots added to pictureBox, then build shape
	if (++currentClicks == maximumClicks) {
		currentClicks = 0;

		GShape^ newShape = formShape(1);
		drawShape(gr, newShape);
	}

	delete gr;
	pictureBox->Refresh();

}
inline System::Void BresenhamAlgos::MainWinForm::randomItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	GShape^ shape;

	int const maxRad = 100;

	Random^ rand = gcnew Random();
	Point randPoint = Point(rand->Next(pictureBox->Width), rand->Next(pictureBox->Height));

	if (ellipseItem->Checked) {
		shape = gcnew GEllipse(randPoint,
			rand->Next(maxRad),
			rand->Next(maxRad));
	}
	else if (circleItem->Checked) {
		Point oneMorePoint = Point(randPoint.X + rand->Next(maxRad),
			randPoint.Y + rand->Next(maxRad));

		shape = gcnew GCircle(randPoint, oneMorePoint);
	}
	else if (lineItem->Checked) {
		Point oneMorePoint = Point(rand->Next(pictureBox->Width), rand->Next(pictureBox->Height));
		shape = gcnew GLine(randPoint, oneMorePoint);
	}
	else {
		MessageBox::Show("Please, select a shape for random building", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	shape->setDepth(rand->Next(1, 3));
	shape->setColor(Color::FromArgb(rand->Next(255), rand->Next(255), rand->Next(255)));


	drawShape(shape);

}


#pragma region Click on menu Items

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

	shapes->Clear();

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
// Color setting
inline System::Void BresenhamAlgos::MainWinForm::colorItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	colorDialog->ShowDialog();
}
// Save
inline System::Void BresenhamAlgos::MainWinForm::saveItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	saveDialog->ShowDialog();

}
inline System::Void BresenhamAlgos::MainWinForm::saveDialog_FileOk(System::Object ^ sender, System::ComponentModel::CancelEventArgs ^ e) {

	StreamWriter^ sw = gcnew StreamWriter(saveDialog->FileName);

	for each (GShape^ shape in shapes)
	{
		// todo exception
		sw->WriteLine(shape->ToString());
	}
	sw->Close();
}
// Open
inline System::Void BresenhamAlgos::MainWinForm::openItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	
	openDialog->ShowDialog();

	try
	{
		GShapeParser^ parser = gcnew GShapeParser();
		GShape^ shape = parser->parse("Ellipse;-16744193;1;{X=343,Y=332};40;20");
	}
	catch (ArgumentException^ e)
	{
		MessageBox::Show(e->Message, "Error while reading file!", 
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	
	int a = 12;
}
inline System::Void BresenhamAlgos::MainWinForm::openDialog_FileOk(System::Object ^ sender, System::ComponentModel::CancelEventArgs ^ e) {

	// Read, parse and save shapes from file 

	array<String^>^ lines = File::ReadAllLines(openDialog->FileName);
	List<GShape^>^ newList = gcnew List<GShape^>();
	GShapeParser^ parser = gcnew GShapeParser();
	try
	{
		for each (String^ line in lines)
		{
			newList->Add(parser->parse(line));
		}
	}
	catch (ArgumentException^ e)
	{
		MessageBox::Show(e->Message, "Error while reading file!",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		newList->Clear();
		return;
	}

	clearItem->PerformClick();

	// Draw shapes
	Graphics^ gr = Graphics::FromImage(bm);
	for each (GShape^ shape in newList)
	{
		drawShape(gr, shape);
	}

	delete gr;
	pictureBox->Refresh();

}
#pragma endregion

// Button exchanging height and width values
inline void BresenhamAlgos::MainWinForm::exchangeButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Decimal tmp = numericHeight->Value;
	numericHeight->Value = numericWidth->Value < numericHeight->Maximum ? numericWidth->Value : numericHeight->Maximum;
	numericWidth->Value = tmp < numericWidth->Maximum ? tmp : numericWidth->Maximum;
}


// Length between 2 dots
int BresenhamAlgos::MainWinForm::length(Point ^ a, Point ^ b)
{
	int len = (int)Math::Sqrt(Math::Pow(a->X - b->X, 2) + Math::Pow(a->Y - b->Y, 2));
	return len;
}
// Draw dot (rectangle)
inline void BresenhamAlgos::MainWinForm::draw_dot(Graphics^ gr, int x, int y, Color col, int size) {
	gr->FillRectangle(gcnew SolidBrush(col), x - (size / 2), y - (size / 2), size, size);
}
// Get Shape by menuItems and points
GShape ^ BresenhamAlgos::MainWinForm::formShape(int depth)
{
	// variable just to make code more readable
	Point^ p1 = points[0];
	Point^ p2 = points[1];

	GShape^ shape;

	if (lineItem->Checked) {
		shape = gcnew GLine(colorDialog->Color, depth, p1, p2);
	}
	else if (circleItem->Checked) {
		shape = gcnew GCircle(colorDialog->Color, depth, p1, p2);
	}
	else if (ellipseItem->Checked) {
		int width = (int)numericWidth->Value;
		int height = (int)numericHeight->Value;
		shape = gcnew GEllipse(colorDialog->Color, depth, p1, width, height);
	}
	else if (strokeFillItem->Checked) {
		shape = gcnew StrokeFill(colorDialog->Color, bm, p1);
	}
	return shape;
}
// Draw shape
void BresenhamAlgos::MainWinForm::drawShape(Graphics^ gr, GShape^ shape)
{
	List<Tuple<int, int>^>^ drawn_dots;

	drawn_dots = shape->getPixels();
	shapes->Add(shape);

	// Draw all points from list
	for (int i = 0; i < drawn_dots->Count; i++) {
		Tuple<int, int>^ p = drawn_dots[i];
		draw_dot(gr, p->Item1, p->Item2, shape->getColor(), shape->getDepth());
	}
}
void BresenhamAlgos::MainWinForm::drawShape(GShape ^ shape)
{
	Graphics^ gr = Graphics::FromImage(bm);
	drawShape(gr, shape);
	delete gr;
	pictureBox->Refresh();
}

// Stroke filling with seed point
inline System::Void BresenhamAlgos::MainWinForm::strokeFillItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged((ToolStripMenuItem^)sender, 1);
}
