#include "Clipping.h"

int Clipping::defineCode(Point ^ p)
{
	int res = 0;
	if (p->X < _min->X)
		res |= 1;
	if (p->X > _max->X)
		res |= 2;
	if (p->Y < _min->Y)
		res |= 4;
	if (p->Y > _max->Y)
		res |= 8;
	
	return res;
}

Clipping::Clipping(Point ^ a, Point ^ b)
{
	this->_min = gcnew Point(Math::Min(a->X, b->X), Math::Min(a->Y, b->Y));
	this->_max = gcnew Point(Math::Max(a->X, b->X), Math::Max(a->Y, b->Y));
}

LinePosition Clipping::identifyPosition(GLine ^ line)
{
	int code1 = defineCode(line->getFirst());
	int code2 = defineCode(line->getSecond());

	if (code1 == code2 && code2 == 0) {
		return LinePosition::Visible;
	}
	if ((code1 & code2) > 0) {
		return LinePosition::Invisible;
	}
	return LinePosition::ClarificationRequires;
}
