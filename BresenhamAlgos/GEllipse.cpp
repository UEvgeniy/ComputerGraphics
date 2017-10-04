#include "GEllipse.h"

GEllipse::GEllipse(Point ^ center, int width, int height) :GEllipse(Color::Black, 2, center, width, height) { }

GEllipse::GEllipse(Color  color, int depth, Point ^ center, int width, int height) : GShape(color, depth)
{
	this->_center = center;
	this->_width = width;
	this->_height = height;
}

List<Tuple<int, int>^>^ GEllipse::getPixels()
{
	return Bresenham::buildEllipse(_center->X, _center->Y, _width, _height);
}

System::String ^ GEllipse::ToString()
{
	return System::String::Format("Ellipse;{0};{1};{2};{3};{4}",
		this->_color.ToArgb(),
		this->_depth,
		this->_center,
		this->_width,
		this->_height
		);
}
