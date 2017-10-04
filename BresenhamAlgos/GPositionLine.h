#pragma once
#include "GLine.h"
#include "Clipping.h"
ref class GPositionLine :
	public GLine
{
private:
	GLine^ _line;
	Point^ _min;
	Point^ _max; 
	LinePosition _pos;

	bool inBorder(Tuple<int, int>^ point);

public:
	GPositionLine(GLine^ line, Point^ a, Point^ b, LinePosition pos);

	List<Tuple<int, int>^>^ getPixels() override;
	
};

