#pragma once
#include "GShape.h"
ref class StrokeFill :
	public GShape
{
private:

	Point^ _seed;
	Bitmap^ _bm;
	List<pair>^ _pixels;

	void func(Color^ redrawnColor, int x, int y);
	bool isBorder(Color^ redrawnColor, int x, int y);
	Color^ getPixColor(int x, int y);

	bool canMoveRight(int x, int y, Color^ redrawnColor);
	bool canMoveLeft(int x, int y, Color^ redrawnColor);
	void inspectPoints(int xMin, int xMax, int y, Stack<pair>^ stack, Color^ redrawnCol);

public:
	StrokeFill(Color col, Bitmap^ bm, Point^ seed);

	List<pair>^ getPixels() override;
	System::String^ ToString() override;
};

