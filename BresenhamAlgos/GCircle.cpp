#include "GCircle.h"

GCircle::GCircle(Point ^ center, Point ^ circlePoint) : GCircle(Color::Black, 2, center, circlePoint)
{ }


GCircle::GCircle(Color color, int depth, Point^ center, Point^ circlePoint) : GShape(color, depth)
{ 
	this->_center = center;
	this->_cPoint = circlePoint;
}

List<pair>^ GCircle::getPixels()
{
	return Bresenham::buildCircle(_center->X, _center->Y, _cPoint->X, _cPoint->Y);
}

System::String ^ GCircle::ToString()
{
	return System::String::Format("Circle;{0};{1};{2};{3}",
		this->_center,
		this->_cPoint,
		this->_color,
		this->_depth);
}
