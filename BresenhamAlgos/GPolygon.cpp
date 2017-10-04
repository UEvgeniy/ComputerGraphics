#include "GPolygon.h"



List<GLine^>^ GPolygon::topsToEdges(List<Point>^ points)
{
	int len = points->Count;
	List<GLine^>^ res = gcnew List<GLine^>(len);
	for (int i = 0; i < len; i++) {

		res->Add(gcnew GLine(getColor(), getDepth(), 
			points[i], points[(i + 1) % len]));
	}
	return res;
}

GPolygon::GPolygon(List<Point>^ points) :  GPolygon(points, Color::Black, 1)
{
}

GPolygon::GPolygon(List<Point>^ points, Color col, int depth) : GShape(col, depth)
{
	edges = topsToEdges(points);
	tops = points;
}

List<GLine^>^ GPolygon::getEdges()
{
	return edges;
}

List<Point>^ GPolygon::getTops()
{
	return tops;
}

List<Tuple<int, int>^>^ GPolygon::getPixels()
{
	List<Tuple<int, int>^>^ res = gcnew List<Tuple<int, int>^>();
	
	for each (GLine^ line in edges)
	{
		res->AddRange(line->getPixels());
	}

	return res;
}

System::String ^ GPolygon::ToString()
{
	String^ res = System::String::Format("Polygon;{0};{1};",
		this->_color.ToArgb(),
		this->_depth
	);
	for each (Point p in tops)
	{
		res += p + ";";
	}

	return res;
}


GPolygon::~GPolygon()
{
}
