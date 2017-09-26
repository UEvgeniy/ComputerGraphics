#pragma once
#include "GShape.h"
ref class GLine :
	public GShape
{
private:
	Point^ _p1;
	Point^ _p2;
public:
	GLine(Color col, int depth, Point^ p1, Point^ p2);
	GLine(Point p1, Point^ p2);

	Point^ getFirst();
	Point^ getSecond();

	List<pair>^ getPixels() override;
};

