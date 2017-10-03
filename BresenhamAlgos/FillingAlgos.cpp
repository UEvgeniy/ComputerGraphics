#include "FillingAlgos.h"
#include <cliext/map>
using namespace System;
using namespace cliext;

bool FillingAlgos::canMoveRight(int x, int y, Color^ redrawnColor, Bitmap^ bm) {
	if (x + 1 >= bm->Width)
		return false;

	return bm->GetPixel(x, y).Equals(redrawnColor) && bm->GetPixel(x + 1, y).Equals(redrawnColor);
}
bool FillingAlgos::canMoveLeft(int x, int y, Color^ redrawnColor, Bitmap^ bm) {
	if (x - 1 < 0)
		return false;

	return bm->GetPixel(x - 1, y).Equals(redrawnColor);
}


void FillingAlgos::inspectPoints(int xMin, int xMax, int y, Stack<Tuple<int, int>^>^ stack, Color  redrawnCol, Bitmap ^ bm)
{
	int curX = xMin;
	while (curX < xMax ||
		curX < bm->Width && bm->GetPixel(curX, y).ToArgb() == redrawnCol.ToArgb()) {

		if ((bm->GetPixel(curX, y).ToArgb() == redrawnCol.ToArgb()
			&& !canMoveRight(curX, y, redrawnCol, bm)) || curX == bm->Width - 1) {

			
			Tuple<int, int>^ t = gcnew Tuple<int, int>(curX, y);
			stack->Push(t);
			
		}
		curX++;
	}
}


FillingAlgos::FillingAlgos()
{
}

void FillingAlgos::strokeWithSeedPoint(Bitmap ^ bm, Color  col, PictureBox^ pb, int x, int y)
{
	Graphics^ gr = Graphics::FromImage(bm);
	SolidBrush^ b = gcnew SolidBrush(col);

	Color redrawnCol = bm->GetPixel(x, y);

	if (redrawnCol.ToArgb() == col.ToArgb()) {
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
		if (!(bm->GetPixel(p->Item1, p->Item2).ToArgb() == redrawnCol.ToArgb())) {
			continue;
		}

		curX = p->Item1;
		curY = p->Item2;

		// Go left to the border and fill in
		do {
			gr->FillRectangle(b, curX, curY, 1, 1);
		} while (canMoveLeft(curX--, curY, redrawnCol, bm));
		curX++;
		
		pb->Refresh();
		System::Threading::Thread::Sleep(10);


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

void FillingAlgos::XORfill(Bitmap ^ bm, Color paint, Color default, List<GPolygon^>^ polygons, PictureBox^ pb)
{
	Bitmap^ backup = bm->Clone(Rectangle(0, 0, bm->Width, bm->Height), bm->PixelFormat);
	//List<Tuple<int, int>^>^ pixels = polygons[0]->getPixels();
	Graphics^ gr = Graphics::FromImage(bm);
	SolidBrush^ br = gcnew SolidBrush(paint);
	SolidBrush^ def = gcnew SolidBrush(default);

	for each (GPolygon^ polygon in polygons) {

		List<GLine^>^ edges = polygon->getEdges(); // ->GetRange(0, 2);
		array<int>^ crossed = gcnew array<int>(polygon->getTops()->Count);
		
		map<int, int>^ myMap = gcnew map<int, int>();
		for each (Point p in polygon->getTops()) {
			myMap->insert(map<int, int>::make_value(p.Y, 0));
		}

		for each (GLine^ line in edges)
		{
			List<Tuple<int, int>^>^ dots = line->getPixels();
			for (int i = 0; i < dots->Count; i++) {

				int y = dots[i]->Item2;

				if (dots[i]->Item2 == Math::Max(line->getFirst()->Y, line->getSecond()->Y)) {
					continue;
				}

				// if next pixel is border too
				if (dots->Contains(gcnew Tuple<int, int>(dots[i]->Item1 + 1, y))) {
					continue;
				}

				// count how many times top crossed edges
				if (myMap->find(y) != myMap->end()) {
					myMap[y]++;
				}
				//for (int j = 0; j < polygon->getTops()->Count; j++) {
				//	if (polygon->getTops()[j].Y == y) {
				//		crossed[j]++;
				//	}
				//}

				for (int x = dots[i]->Item1 + 1; x < bm->Width; x++) {

					if (bm->GetPixel(x, y).ToArgb() != paint.ToArgb()) {
						gr->FillRectangle(br, x, y, 1, 1);
					}
					else {
						gr->FillRectangle(def, x, y, 1, 1);
					}
				}
				pb->Refresh();
			}
		}

		/*List<Point>^ tops = polygon->getTops();
		for (int i = 0; i < tops->Count; i++) {
			if (myMap[tops[i].Y] % 2 == 0) {
				myMap[tops[i].Y]++;
				continue;
			}
			
			for (int x = tops[i].X + 1; x < bm->Width; x++) {

				if (bm->GetPixel(x, tops[i].Y).ToArgb() != col.ToArgb()) {
					gr->FillRectangle(br, x, tops[i].Y, 1, 1);
				}
				else {
					gr->FillRectangle(gcnew SolidBrush(Color::White), x, tops[i].Y, 1, 1);
				}
			}
			pb->Refresh();
		}
		*/

		
	}
	delete gr;
}

