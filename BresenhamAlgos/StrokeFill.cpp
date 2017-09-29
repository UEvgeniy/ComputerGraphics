#include "StrokeFill.h"

StrokeFill::StrokeFill(Color col, Bitmap^ bm, Point^ seed) : GShape(col, 1)
{
	this->_pixels = gcnew List<Tuple<int, int>^>();
	this->_seed = seed;
	this->_bm = bm;
}


void StrokeFill::func(Color^ redrawnColor, int x, int y)
{
	int curX = x;
	int curY = y;
	// Go left and fill pixels
	while (curX >= 0 && _bm->GetPixel(curX, curY).Equals(redrawnColor)) {
		_pixels->Add(make_pair(curX--, curY));
	}

	// Go down and right
	if (++curY == _bm->Height) {
		return;
	}


	//while (curX <= x) {
	//	if (_bm->GetPixel(curX, curY).Equals(redrawnColor) && isBorder(redrawnColor, curX + 1, curY)) {
	//		func(redrawnColor, curX, curY);
	//	}
	//	curX++;
	//}
	//while (curX < _bm->Width && ! getColor(curX, curY)->Equals(getColor(curX + 1, curY))) {
	//	curX++;
	//};

	if (_bm->GetPixel(curX, curY).Equals(redrawnColor)) {
		func(redrawnColor, curX, curY);
	}
}

bool StrokeFill::isBorder(Color ^ redrawnColor, int x, int y)
{
	// Pixel is a border, if it has any color except redrawn one or fill color
	return !_bm->GetPixel(x, y).Equals(redrawnColor) &&
		!_bm->GetPixel(x, y).Equals(this->_color);
}

Color ^ StrokeFill::getPixColor(int x, int y)
{
	return _bm->GetPixel(x, y);
}

// 
bool StrokeFill::canMoveRight(int x, int y, Color^ redrawnColor) {
	if (x + 1 >= _bm->Width)
		return false;

	return _bm->GetPixel(x, y).Equals(redrawnColor) && _bm->GetPixel(x + 1, y).Equals(redrawnColor);
}
bool StrokeFill::canMoveLeft(int x, int y, Color^ redrawnColor) {
	if (x - 1 < 0)
		return false;

	return _bm->GetPixel(x - 1, y).Equals(redrawnColor);
}

void StrokeFill::inspectPoints(int xMin, int xMax, int y, Stack<Tuple<int, int>^>^ stack, Color^ redrawnCol)
{
	int curX = xMin;
	while (curX < xMax ||
		curX < _bm->Width && getPixColor(curX, y)->Equals(redrawnCol) /*canMoveRight(curX, curY, redrawnCol)*/) {

		if ((getPixColor(curX, y)->Equals(redrawnCol)
			&& !canMoveRight(curX, y, redrawnCol)) || curX == _bm->Width - 1) {

			Tuple<int, int>^ t = make_pair(curX, y);

			if (!_pixels->Contains(t)) {
				stack->Push(make_pair(curX, y));
			}
		}
		curX++;
	}
}

List<Tuple<int, int>^>^ StrokeFill::getPixels()
{
	if (_pixels->Count > 0) {
		return _pixels;
	}

	Color^ redrawnCol = _bm->GetPixel(_seed->X, _seed->Y);
	Stack<Tuple<int, int>^>^ points = gcnew Stack<Tuple<int, int>^>();
	
	int curX = _seed->X;
	int curY = _seed->Y;

	// Go right to the border
	while (canMoveRight(curX, curY, redrawnCol)) {
		curX++;
	}

	// First seed point
	points->Push(make_pair(curX, curY));

	while (points->Count > 0) {

		Tuple<int, int>^ p = points->Pop();

		// Already redrawned pixel
		if (_pixels->Contains(p)) {
			continue;
		}

		curX = p->Item1;
		curY = p->Item2;

		// Go left to the border and fill in

		do {
			_pixels->Add(make_pair(curX, curY));
		}
		while (canMoveLeft(curX--, curY, redrawnCol));
		curX++;

		List<Tuple<int, int>^>^ tmp = gcnew List<Tuple<int, int>^>();
		
		//tmp->Add(gcnew Tuple<int, int>(2, 3));
		//if (tmp->Contains(gcnew Tuple<int, int>(2, 3))) {
		//	return _pixels;
		//}

		// Go down
		if (curY + 1 < _bm->Height) {
			inspectPoints(curX, p->Item1, curY + 1, points, redrawnCol);
		}

		// Go up
		if (curY - 1 >= 0 && !points->Contains(make_pair(curX, curY - 1))) {
			inspectPoints(curX, p->Item1, curY - 1, points, redrawnCol);
		}
		int a = 12;
	}

	return _pixels;
}

System::String ^ StrokeFill::ToString()
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}
