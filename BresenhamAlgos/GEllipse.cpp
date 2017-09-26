#include "GEllipse.h"

GEllipse::GEllipse(Point ^ center, int width, int height) :GEllipse(Color::Black, 2, center, width, height) { }

GEllipse::GEllipse(Color  color, int depth, Point ^ center, int width, int height) : GShape(color, depth)
{
	this->_center = center;
	this->_width = width;
	this->_height = height;
}

List<pair>^ GEllipse::getPixels()
{
	return Bresenham::buildEllipse(_center->X, _center->Y, _width, _height);
}
