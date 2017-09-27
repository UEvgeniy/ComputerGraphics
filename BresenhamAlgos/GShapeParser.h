#pragma once
#include "GShape.h"
#include "GLine.h"
#include "GCircle.h"
#include "GEllipse.h"

using namespace System;

ref class GShapeParser
{
private:
	array<Point>^ parseTwoPoints(String^ props, String^ type);
	GEllipse^ parseEllipse(String^ props);

public:

	GShapeParser();
	GShape^ parse(String^ str);

};

