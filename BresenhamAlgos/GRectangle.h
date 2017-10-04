#pragma once
#include "GShape.h"
ref class GRectangle :
	public GShape
{
private :
	int _xMin, _xMax, _yMin, _yMax;
	List<Tuple<int, int>^>^ _pixels;
public:
	GRectangle(Point p1, Point p2);

	List<Tuple<int, int>^>^ getPixels() override;
	System::String^ ToString() override;

	Point getLeftTop();
	Point getRightButtom();

	~GRectangle();
};

