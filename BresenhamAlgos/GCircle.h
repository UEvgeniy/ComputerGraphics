#pragma once
#include "GShape.h"


ref class GCircle :
	public GShape
{
private:
	Point^ _center;
	Point^ _cPoint;

public:
	GCircle(Point^ center, Point^ circlePoint);
	GCircle(Color color, int depth, Point^ center, Point^ circlePoint);

	List<Tuple<int, int>^>^ getPixels() override;
	System::String^ ToString() override;

};

