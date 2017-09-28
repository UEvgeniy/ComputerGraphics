#pragma once
#include "GShape.h"
ref class StrokeFill :
	public GShape
{
private:
	Point^ _seed;
public:
	StrokeFill(Color col, Point^ seed);

	List<pair>^ getPixels() override;
	System::String^ ToString() override;
};

