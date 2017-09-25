#include "GShape.h"

GShape::GShape(Color ^ col, int depth)
{
	setColor(col);
	setDepth(depth);
}

void GShape::setColor(Color ^ col)
{
	this->_color = col;
}

Color ^ GShape::getColor()
{
	return this->_color;
}

int GShape::getDepth()
{
	return this->_depth;
}

void GShape::setDepth(int depth)
{
	this->_depth = depth;
}

