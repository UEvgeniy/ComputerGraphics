#pragma once
#include "Filling.h"
ref class StrokeWithSeedPoint :
	public Filling
{
private:
	int _x;
	int _y;
	Color _redrawnCol;

	bool canMoveRight(int x, int y);
	bool canMoveLeft(int x, int y);
	void inspectPoints(int xMin, int xMax, int y, Stack<Tuple<int, int>^>^ stack);


public:
	StrokeWithSeedPoint(Bitmap^ bm, Color col, int x, int y);
	void fill() override;

	~StrokeWithSeedPoint();
};

