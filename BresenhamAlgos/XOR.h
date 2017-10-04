#pragma once
#include "Filling.h"
#include "GPolygon.h"
ref class XOR :
	public Filling
{
	Color _defColor;
	List<GPolygon^>^ _polygons;

public:

	XOR(Bitmap^ bm, Color col, Color default, List<GPolygon^>^ polygons);

	void fill() override;
	~XOR();
};

