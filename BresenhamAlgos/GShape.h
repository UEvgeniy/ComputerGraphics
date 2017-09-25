#pragma once
#include "Bresenham.h"

using namespace System::Drawing;

ref class GShape
{
protected:
	Color^ _color;
	int _depth;

	GShape(Color^ col, int depth);

public:
	
	void setColor(Color^ col);
	Color^ getColor();

	int getDepth();
	void setDepth(int depth);

	virtual List<pair>^ getPixels() = 0; //must be overriden in derived classes
};

