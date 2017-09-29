#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

ref class StrokeFilling
{
private:
	StrokeFilling();

	static bool canMoveRight(int x, int y, Color^ redrawnColor, Bitmap^ bm);
	static bool canMoveLeft(int x, int y, Color^ redrawnColor, Bitmap^ bm);
	static void inspectPoints(int xMin, int xMax, int y, Stack<Tuple<int, int>^>^ stack, Color^ redrawnCol, Bitmap^ bm);


public:
	static void fill(Bitmap^ bm, Color col, int x, int y);
};

