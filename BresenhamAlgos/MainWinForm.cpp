#include <Windows.h>

#include "MainWinForm.h"
#include "Bresenham.h"
#include "AboutForm.h"

#include "GLine.h"
#include "GEllipse.h"
#include "GCircle.h"
#include "GPolygon.h"
#include "GRectangle.h"

#include "GShapeParser.h"
#include "GPositionLine.h"
#include "Clipping.h"

#include "StrokeWithSeedPoint.h"
#include "XOR.h"

#include "FillingAlgos.h"


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
	clippingShapes = gcnew List<GShape^>();

	// Points clicked on the picture box
	points = gcnew List<Point>();

	// Group of toolMenuItems (only one can be checked)
	// todo separate method
	exclusiveShapes = gcnew List<ToolStripMenuItem^>();
	exclusiveShapes->Add(lineItem);
	exclusiveShapes->Add(circleItem);
	exclusiveShapes->Add(ellipseItem);
	exclusiveShapes->Add(strokeFillItem);
	exclusiveShapes->Add(clippingItem);
	exclusiveShapes->Add(polygonItem);
	exclusiveShapes->Add(xorItem);

	clippingMode = gcnew List<ToolStripMenuItem^>();
	clippingMode->Add(initDataItem);
	clippingMode->Add(colorizeItem);
	clippingMode->Add(clipLinesItem);

	delays = gcnew List<ToolStripMenuItem^>();
	delays->Add(noDelayItem);
	delays->Add(ms10Item);
	delays->Add(ms500Item);

	// Default selection
	lineItem->PerformClick();
	colorizeItem->PerformClick();
	noDelayItem->PerformClick();

	// Properties for labels
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
	//points[points->Count - 1] = Point(e->Location.X, e->Location.Y);
	points->Add(Point(e->Location.X, e->Location.Y));

	//Polygon drawing
	if (polygonItem->Checked) {
		polygonBuild();
	}

	if (!strokeFillItem->Checked && !xorItem->Checked) {
		draw_dot(gr, e->Location.X, e->Location.Y, 2);
	}

	// If all required dots added to pictureBox, then build shape
	if (points->Count == maximumClicks) {
		
		// Stroke filling
		if (strokeFillItem->Checked) {
			StrokeWithSeedPoint^ f = gcnew StrokeWithSeedPoint(bm, colorDialog->Color, points[0].X, points[0].Y);
			f->onIteration += gcnew IterationDel(this, &BresenhamAlgos::MainWinForm::IterationHandler);
			f->fill();
		}
		// Clipping
		else if (clippingItem->Checked) {
			clipLines();

		}
		else {
			GShape^ newShape = formShape(1);
			drawShape(gr, newShape);
			shapes->Add(newShape);
		}
		points->Clear();
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

	shapes->Add(shape);
	drawShape(shape);

}


#pragma region Click on menu Items

// Select line
inline System::Void BresenhamAlgos::MainWinForm::lineItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged(exclusiveShapes, (ToolStripMenuItem^)sender);
	maximumClicks = 2;
}
// Select circle
inline System::Void BresenhamAlgos::MainWinForm::circleItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged(exclusiveShapes, (ToolStripMenuItem^)sender);
	maximumClicks = 2;
}
// Select ellipse
inline System::Void BresenhamAlgos::MainWinForm::ellipseItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged(exclusiveShapes, (ToolStripMenuItem^)sender);
	maximumClicks = 1;
	groupBox->Visible = ellipseItem->Checked;
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
	points->Clear();

	gr->Clear(pictureBox->BackColor);

	delete gr;
	pictureBox->Refresh();
}
// Universal method for changing checked property
inline void BresenhamAlgos::MainWinForm::itemChanged(List<ToolStripMenuItem^>^ list, ToolStripMenuItem ^ item) {

	if (item->Checked) {
		return;
	}
	points->Clear();

	// update checked state of items
	for (int i = 0; i < list->Count; i++) {
		list[i]->Checked = false;
	}
	item->Checked = true;
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
		shapes->Add(shape);
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
void BresenhamAlgos::MainWinForm::draw_dot(Graphics ^ gr, int x, int y, int size)
{
	draw_dot(gr, x, y, Color::Black, size);
}

// Get Shape by menuItems and points
GShape ^ BresenhamAlgos::MainWinForm::formShape(int depth)
{
	// variable just to make code more readable
	Point^ p1 = points[0];

	GShape^ shape;

	if (lineItem->Checked) {
		Point^ p2 = points[1];
		shape = gcnew GLine(colorDialog->Color, depth, p1, p2);
	}
	else if (circleItem->Checked) {
		Point^ p2 = points[1];
		shape = gcnew GCircle(colorDialog->Color, depth, p1, p2);
	}
	else if (ellipseItem->Checked) {
		int width = (int)numericWidth->Value;
		int height = (int)numericHeight->Value;
		shape = gcnew GEllipse(colorDialog->Color, depth, p1, width, height);
	}
	else if (polygonItem->Checked)  {

		List<Point>^ list = gcnew List<Point>();
		for (int i = 0; i < points->Count - 1; i++)
		{
			
			list->Add(points[i]);
		}
		shape = gcnew GPolygon(list, colorDialog->Color, depth);
		maximumClicks = 100;		
	}
	
	return shape;
}
// Draw shape
void BresenhamAlgos::MainWinForm::drawShape(Graphics^ gr, GShape^ shape)
{
	List<Tuple<int, int>^>^ drawn_dots;

	drawn_dots = shape->getPixels();

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

void BresenhamAlgos::MainWinForm::clipLines()
{
	//Add rectangle
	GRectangle^ rect;
	if (points->Count == 0) {
		rect =  (GRectangle^)clippingShapes[0];
	}
	else {
		rect = gcnew GRectangle(points[0], points[1]);
	}
	clippingShapes->Clear();
	clippingShapes->Add(rect);

	// Start clip all lines
	Clipping^ clip = gcnew Clipping(rect->getLeftTop(), rect->getRightButtom());

	for each (GShape^ shape in shapes) {
		LinePosition pos = clip->identifyPosition((GLine^)shape);
		GLine^ newLine = gcnew GPositionLine((GLine^)shape, rect->getLeftTop(), rect->getRightButtom(), pos);
		clippingShapes->Add(newLine);
	}

	// Drawing shapes (according to 3 modes)
	Graphics^ gr = Graphics::FromImage(bm);
	gr->Clear(pictureBox->BackColor);
	// todo modify logic
	if (initDataItem->Checked) {
		for each (GShape^ s in shapes) {
			drawShape(gr, s);
		}
		drawShape(clippingShapes[0]);
	}
	else if (colorizeItem->Checked) {
		for each (GShape^ s in shapes) {
			drawShape(gr, s);
		}
		for each (GShape^ s in clippingShapes) {
			drawShape(gr, s);
		}
	}
	else if (clipLinesItem->Checked) {
		for each (GShape^ s in clippingShapes){
			if (s->getColor().ToArgb() != Color::Red.ToArgb()) {
				drawShape(gr, s);
			}
		}
	}
	delete gr;
	pictureBox->Refresh();
}

void BresenhamAlgos::MainWinForm::drawRect(Point ^ a, Point ^ b)
{
	Graphics^ gr = Graphics::FromImage(bm);

	gr->DrawRectangle(gcnew Pen(colorDialog->Color), 
		System::Math::Min(a->X, b->X), System::Math::Min(a->Y, b->Y), 
		System::Math::Abs(a->X - b->X), System::Math::Abs(a->Y - b->Y));


	delete gr;
	pictureBox->Refresh();
}

void BresenhamAlgos::MainWinForm::polygonBuild()
{
	if (points->Count == 1) {
		return;
	}
	Point^ initial = points[0];
	Point^ current = points[points->Count - 1];

	// todo magic number
	if (Math::Abs(initial->X - current->X) > 5
		|| Math::Abs(initial->Y - current->Y) > 5) {
		return;
	}

	if (1 < points->Count && points->Count < 4) {
		MessageBox::Show("Minimum 3 tops required for building polygon", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		points->Clear();
		return;
	}

	maximumClicks = points->Count;
	
}

void BresenhamAlgos::MainWinForm::IterationHandler(bool needShapesRedraw)
{
	if (delay == 0) {
		return;
	}

	System::Threading::Thread::Sleep(delay);
	
	if (needShapesRedraw) {
		for each (GShape^ s in shapes) {
			drawShape(s);
		}
	}

	pictureBox->Refresh();
}

inline System::Void BresenhamAlgos::MainWinForm::clippingItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	
	if (clippingItem->Checked) {
		return;
	}

	// Find all lines
	List<GLine^>^ onlyLines = gcnew List<GLine^>();
	for each (GShape^ shape in shapes) {
		// todo get type better
		if (shape->GetType()->Equals(Type::GetType("GLine"))) {
			onlyLines->Add((GLine^)shape);
		}
	}

	if (onlyLines->Count < shapes->Count) {
		if (MessageBox::Show("The field contains another figures except lines. Do you want to delete them to continue?", 
			"Clear", MessageBoxButtons::YesNo, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes) {
			return;
		}

		clearItem->PerformClick();
		Graphics^ gr = Graphics::FromImage(bm);
		for each (GLine^ line in onlyLines)
		{
			shapes->Add(line);
			drawShape(gr, line);
		}
		delete gr;
		pictureBox->Refresh();
	}

	itemChanged(exclusiveShapes, (ToolStripMenuItem^)sender);
	maximumClicks = 2;
}

inline System::Void BresenhamAlgos::MainWinForm::xorItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	List<GPolygon^>^ polygons = gcnew List<GPolygon^>();
	for each (GShape^ shape in shapes)
	{
		if (shape->GetType()->Equals(Type::GetType("GPolygon"))) {
			polygons->Add((GPolygon^)shape);
		}
	}
	if (polygons->Count == 0) {
		MessageBox::Show("At least one polygon required for XOR filling", "Error", 
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	itemChanged(exclusiveShapes, (ToolStripMenuItem^)sender);


	XOR^ xor = gcnew XOR(bm, colorDialog->Color, pictureBox->BackColor, polygons);
	xor->onIteration += gcnew IterationDel(this, &BresenhamAlgos::MainWinForm::IterationHandler);
	xor->fill();
	for each (GShape^ s in shapes) {
		drawShape(s);
	}
	pictureBox->Refresh();

}

inline System::Void BresenhamAlgos::MainWinForm::polygonItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged(exclusiveShapes, (ToolStripMenuItem^)sender);
	maximumClicks = 100;
}

inline System::Void BresenhamAlgos::MainWinForm::initDataItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged(clippingMode, (ToolStripMenuItem^)sender);
	if (clippingItem->Checked && clippingShapes->Count > 0) {
		clipLines();
	}
}

inline System::Void BresenhamAlgos::MainWinForm::colorizeItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged(clippingMode, (ToolStripMenuItem^)sender);
	if (clippingItem->Checked && clippingShapes->Count > 0) {
		clipLines();
	}
}

inline System::Void BresenhamAlgos::MainWinForm::clipLinesItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged(clippingMode, (ToolStripMenuItem^)sender);
	if (clippingItem->Checked && clippingShapes->Count > 0) {
		clipLines();
	}
}

// Stroke filling with seed point
inline System::Void BresenhamAlgos::MainWinForm::strokeFillItem_Click(System::Object ^ sender, System::EventArgs ^ e) {
	itemChanged(exclusiveShapes, (ToolStripMenuItem^)sender);
	maximumClicks = 1;
	if (ms500Item->Checked) {
		ms10Item->PerformClick();
	}
}
