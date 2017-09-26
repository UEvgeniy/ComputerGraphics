#include "GLine.h"


GLine::GLine(Color  col, int depth, Point ^ p1, Point ^ p2) : GShape(col, depth)
{
	this->_p1 = p1;
	this->_p2 = p2;
}

GLine::GLine(Point  p1, Point ^ p2) : GLine(Color::Black, 2, p1, p2){ }

Point ^ GLine::getFirst()
{
	return _p1;
}

Point ^ GLine::getSecond()
{
	return _p2;
}

inline List<pair>^ GLine::getPixels() {
	return Bresenham::buildLine(_p1->X, _p1->Y, _p2->X, _p2->Y);
}