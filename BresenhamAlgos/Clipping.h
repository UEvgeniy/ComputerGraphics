#pragma once
#include "GLine.h"
using namespace System::Drawing;

enum LinePosition
{
	Visible, Invisible, ClarificationRequires
};

ref class Clipping
{
private:
	Point^ _min;
	Point^ _max;

	int defineCode(Point^ p);

public:
	Clipping(Point^ a, Point^ b);

	LinePosition identifyPosition(GLine^ line);

};

