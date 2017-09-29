#include "StrokeFilling.h"

using namespace System;

bool StrokeFilling::canMoveRight(int x, int y, Color^ redrawnColor, Bitmap^ bm) {
	if (x + 1 >= bm->Width)
		return false;

	return bm->GetPixel(x, y).Equals(redrawnColor) && bm->GetPixel(x + 1, y).Equals(redrawnColor);
}
bool StrokeFilling::canMoveLeft(int x, int y, Color^ redrawnColor, Bitmap^ bm) {
	if (x - 1 < 0)
		return false;

	return bm->GetPixel(x - 1, y).Equals(redrawnColor);
}


void StrokeFilling::inspectPoints(int xMin, int xMax, int y, Stack<Tuple<int, int>^>^ stack, Color ^ redrawnCol, Bitmap ^ bm)
{
	int curX = xMin;
	while (curX < xMax ||
		curX < bm->Width && bm->GetPixel(curX, y).Equals(redrawnCol)) {

		if ((bm->GetPixel(curX, y).Equals(redrawnCol)
			&& !canMoveRight(curX, y, redrawnCol, bm)) || curX == bm->Width - 1) {

			Tuple<int, int>^ t = gcnew Tuple<int, int>(curX, y);

			if (!stack->Contains(t)) {
				stack->Push(t);
			}
		}
		curX++;
	}
}




StrokeFilling::StrokeFilling()
{
}

void StrokeFilling::fill(Bitmap ^ bm, Color  col, int x, int y)
{
	Graphics^ gr = Graphics::FromImage(bm);
	SolidBrush^ b = gcnew SolidBrush(col);

	Color redrawnCol = bm->GetPixel(x, y);

	if (redrawnCol.Equals(col)) {
		return;
	}

	Stack<Tuple<int, int>^>^ points = gcnew Stack<Tuple<int, int>^>();

	int curX = x;
	int curY = y;

	// Go right to the border
	while (canMoveRight(curX, curY, redrawnCol, bm)) {
		curX++;
	}

	// First seed point
	points->Push(gcnew Tuple<int, int>(curX, curY));

	while (points->Count > 0) {

		Tuple<int, int>^ p = points->Pop();

		// Already redrawned pixel
		if (!bm->GetPixel(p->Item1, p->Item2).Equals(redrawnCol)) {
			continue;
		}

		curX = p->Item1;
		curY = p->Item2;

		// Go left to the border and fill in
		do {
			//_pixels->Add(make_pair(curX, curY));
			gr->FillRectangle(b, curX, curY, 1, 1);
		} while (canMoveLeft(curX--, curY, redrawnCol, bm));
		curX++;


		// Go down
		if (curY + 1 < bm->Height && !points->Contains(gcnew Tuple<int, int>(curX, curY + 1))) {
			inspectPoints(curX, p->Item1, curY + 1, points, redrawnCol, bm);
		}

		// Go up
		if (curY - 1 >= 0 && !points->Contains(gcnew Tuple<int, int>(curX, curY - 1))) {
			inspectPoints(curX, p->Item1, curY - 1, points, redrawnCol, bm);
		}
	}
}
