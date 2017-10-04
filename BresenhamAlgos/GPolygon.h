#pragma once
#include "GShape.h"
#include "GLine.h"
ref class GPolygon :
	public GShape
{
private:
	List<Point>^ tops;
	List<GLine^>^ edges;
	List<GLine^>^ topsToEdges(List<Point>^ points);
public:
	GPolygon(List<Point>^ points);
	GPolygon(List<Point>^ points, Color col, int depth);

	List<GLine^>^ getEdges();
	List<Point>^ getTops();
	List<Tuple<int, int>^>^ getPixels() override;
	System::String^ ToString() override;

	~GPolygon();
};

