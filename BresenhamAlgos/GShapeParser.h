#pragma once
#include "GShape.h"
#include "GLine.h"
#include "GCircle.h"
#include "GEllipse.h"
#include "GPolygon.h"

ref class GShapeParser
{
private:
	GEllipse^ parseEllipse(String^ props);
	List<Point>^ parsePoints(String^ props, String^ type);


public:

	GShapeParser();
	GShape^ parse(String^ str);

};

