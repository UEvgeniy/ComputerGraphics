#pragma once
#include "GShape.h"
ref class GEllipse :
	public GShape
{
private:
	Point^ _center;
	int _width;
	int _height;
public:
	GEllipse(Point^ center, int width, int height);
	GEllipse(Color color, int depth, Point^ center, int width, int height);

	List<pair>^ getPixels() override;
};

