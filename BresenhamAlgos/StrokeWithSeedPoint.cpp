#include "StrokeWithSeedPoint.h"

bool StrokeWithSeedPoint::canMoveRight(int x, int y) {
	if (x + 1 >= _bm->Width)
		return false;
	
	return _bm->GetPixel(x, y).Equals(_redrawnCol) && _bm->GetPixel(x + 1, y).Equals(_redrawnCol);
}
bool StrokeWithSeedPoint::canMoveLeft(int x, int y) {
	if (x - 1 < 0)
		return false;

	return _bm->GetPixel(x - 1, y).Equals(_redrawnCol);
}

void StrokeWithSeedPoint::inspectPoints(int xMin, int xMax, int y, Stack<Tuple<int, int>^>^ stack)
{
	int curX = xMin;
	while (curX < xMax ||
		curX < _bm->Width && _bm->GetPixel(curX, y).ToArgb() == _redrawnCol.ToArgb()) {

		if ((_bm->GetPixel(curX, y).ToArgb() == _redrawnCol.ToArgb()
			&& !canMoveRight(curX, y)) || curX == _bm->Width - 1) {


			Tuple<int, int>^ t = gcnew Tuple<int, int>(curX, y);
			stack->Push(t);

		}
		curX++;
	}
}


StrokeWithSeedPoint::StrokeWithSeedPoint(Bitmap^ bm, Color col, int x, int y) : Filling(bm, col)
{
	this->_x = x;
	this->_y = y;
}

void StrokeWithSeedPoint::fill()
{
	Graphics^ gr = Graphics::FromImage(_bm);
	SolidBrush^ b = gcnew SolidBrush(_color);

	_redrawnCol = _bm->GetPixel(_x, _y);

	if (_redrawnCol.ToArgb() == _color.ToArgb()) {
		return;
	}

	Stack<Tuple<int, int>^>^ points = gcnew Stack<Tuple<int, int>^>();

	int curX = _x;
	int curY = _y;

	// Go right to the border
	while (canMoveRight(curX, curY)) {
		curX++;
	}

	// First seed point
	points->Push(gcnew Tuple<int, int>(curX, curY));

	while (points->Count > 0) {

		Tuple<int, int>^ p = points->Pop();

		// Already redrawned pixel
		if (!(_bm->GetPixel(p->Item1, p->Item2).ToArgb() == _redrawnCol.ToArgb())) {
			continue;
		}

		curX = p->Item1;
		curY = p->Item2;

		// Go left to the border and fill in
		do {
			gr->FillRectangle(b, curX, curY, 1, 1);
		} while (canMoveLeft(curX--, curY));
		curX++;

		// ITERATION IS FINISHED! LAUNCH THREAD SLEEP //
		onIteration(false);

		// Go down
		if (curY + 1 < _bm->Height && !points->Contains(gcnew Tuple<int, int>(curX, curY + 1))) {
			inspectPoints(curX, p->Item1, curY + 1, points);
		}

		// Go up
		if (curY - 1 >= 0 && !points->Contains(gcnew Tuple<int, int>(curX, curY - 1))) {
			inspectPoints(curX, p->Item1, curY - 1, points);
		}
	}
}


StrokeWithSeedPoint::~StrokeWithSeedPoint()
{
}
