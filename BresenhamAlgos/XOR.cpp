#include "XOR.h"


XOR::XOR(Bitmap ^ bm, Color col, Color default, List<GPolygon^>^ polygons) : Filling(bm, col)
{
	_defColor = default;
	_polygons = polygons;
}

void XOR::fill()
{
	Bitmap^ backup = _bm->Clone(Rectangle(0, 0, _bm->Width, _bm->Height), _bm->PixelFormat);
	//List<Tuple<int, int>^>^ pixels = polygons[0]->getPixels();
	Graphics^ gr = Graphics::FromImage(_bm);
	SolidBrush^ br = gcnew SolidBrush(_color);
	SolidBrush^ def = gcnew SolidBrush(_defColor);

	for each (GPolygon^ polygon in _polygons) {

		List<GLine^>^ edges = polygon->getEdges(); 
		array<int>^ crossed = gcnew array<int>(polygon->getTops()->Count);

		//map<int, int>^ myMap = gcnew map<int, int>();
		//for each (Point p in polygon->getTops()) {
		//	myMap->insert(map<int, int>::make_value(p.Y, 0));
		//}

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

				for (int x = dots[i]->Item1 + 1; x < _bm->Width; x++) {

					if (_bm->GetPixel(x, y).ToArgb() != _color.ToArgb()) {
						gr->FillRectangle(br, x, y, 1, 1);
					}
					else {
						gr->FillRectangle(def, x, y, 1, 1);
					}
				}
				
			}
			// ITERATION IS FINISHED! LAUNCH THREAD SLEEP //
			onIteration(true);
		}
	}
	delete gr;
}

XOR::~XOR()
{
}
