#pragma once
#include "GPolygon.h"
using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

ref class FillingAlgos
{
private:
	FillingAlgos();

	static bool canMoveRight(int x, int y, Color^ redrawnColor, Bitmap^ bm);
	static bool canMoveLeft(int x, int y, Color^ redrawnColor, Bitmap^ bm);
	static void inspectPoints(int xMin, int xMax, int y, Stack<Tuple<int, int>^>^ stack, Color redrawnCol, Bitmap^ bm);


public:
	static void strokeWithSeedPoint(Bitmap^ bm, Color col, int x, int y);
	static void XORfill(Bitmap^ bm, Color col, List<GPolygon^>^ polygons, PictureBox^ pb);

};

