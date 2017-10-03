#include "GRectangle.h"


GRectangle::GRectangle(Point p1, Point p2) : GShape(Color::Black, 1)
{
	this->_xMin = Math::Min(p1.X, p2.X);
	this->_xMax = Math::Max(p1.X, p2.X);
	this->_yMin = Math::Min(p1.Y, p2.Y);
	this->_yMax = Math::Max(p1.Y, p2.Y);

	_pixels = gcnew List<Tuple<int, int>^>();
	for (int i = _xMin; i <= _xMax; i++) {
		_pixels->Add(gcnew Tuple<int, int>(i, _yMin));
		_pixels->Add(gcnew Tuple<int, int>(i, _yMax));
	}
	for (int i = _yMin; i <= _yMax; i++) {
		_pixels->Add(gcnew Tuple<int, int>(_xMin, i));
		_pixels->Add(gcnew Tuple<int, int>(_xMax, i));
	}
}

List<Tuple<int, int>^>^ GRectangle::getPixels()
{
	return _pixels;
}

System::String ^ GRectangle::ToString()
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}

Point GRectangle::getLeftTop()
{
	return Point(_xMin, _yMin);
}

Point GRectangle::getRightButtom()
{
	return Point(_xMax, _yMax);
}

GRectangle::~GRectangle()
{
}
