#include "GPositionLine.h"

bool GPositionLine::inBorder(Tuple<int, int>^ point)
{
	return _min->X <= point->Item1 && point->Item1 <= _max->X &&
		_min->Y <= point->Item2 && point->Item2 <= _max->Y;
}

GPositionLine::GPositionLine(GLine ^ line, Point ^ a, Point ^ b, LinePosition pos): GLine(line->getFirst(), line->getSecond())
{
	this->_min = gcnew Point(Math::Min(a->X, b->X), Math::Min(a->Y, b->Y));
	this->_max = gcnew Point(Math::Max(a->X, b->X), Math::Max(a->Y, b->Y));
	this->_pos = pos;
	this->_line = line;
	this->setDepth(_line->getDepth() + 1);
	this->_color = pos == LinePosition::Visible ? Color::Green : 
		(pos == LinePosition::Invisible ? Color::Red : Color::Yellow);
}

List<Tuple<int, int>^>^ GPositionLine::getPixels()
{
	List<Tuple<int, int>^>^ res = gcnew List<Tuple<int, int>^>();

	if (_pos == LinePosition::Visible) {
		res = _line->getPixels();
	}
	else if (_pos == LinePosition::Invisible) {
		res = _line->getPixels();
	}
	else {
		List<Tuple<int, int>^>^ tmp = _line->getPixels();
		for each (Tuple<int, int>^ t in tmp)
		{
			if (inBorder(t)) {
				res->Add(t);
			}
		}
	}

	return res;
}
