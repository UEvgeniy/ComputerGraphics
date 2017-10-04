#include "GShapeParser.h"

using namespace System::Text::RegularExpressions;


GEllipse ^ GShapeParser::parseEllipse(String ^ props)
{
	//Example {X = 343, Y = 332}; 40; 20

	GEllipse^ res;

	Regex^ shapeRegex = gcnew Regex(
		"{X=(?<x>[0-9]+),Y=(?<y>[0-9]+)};(?<w>[0-9]+);(?<h>[0-9]+)"
	);

	Match^ m = shapeRegex->Match(props);

	if (m->Success) {
		Point^ p = Point(
			Int32::Parse(m->Groups["x"]->Value),
			Int32::Parse(m->Groups["y"]->Value));
		int width = Int32::Parse(m->Groups["w"]->Value);
		int height = Int32::Parse(m->Groups["h"]->Value);

		res = gcnew GEllipse(p, width, height);
	}
	else {
		throw gcnew ArgumentException(String::Format("Incorrect Ellipse properies: {0}", props));
	}


	return res;
}


List<Point> ^ GShapeParser::parsePoints(String ^ props, String^ type)
{
	// Example {X=351,Y=125};{X=211,Y=120};{X=182,Y=230};{X=289,Y=303};{X=272,Y=207};

	List<Point> ^ res = gcnew List<Point>();

	if (props->Equals(String::Empty)) {
		return res;
	}

	Regex^ shapeRegex = gcnew Regex(
		"{X=(?<x1>[0-9]+),Y=(?<y1>[0-9]+)};(?<rest>\.*)"
	);

	Match^ m = shapeRegex->Match(props);

	if (m->Success) {
		res->Add(Point(
			Int32::Parse(m->Groups["x1"]->Value),
			Int32::Parse(m->Groups["y1"]->Value)));
		res->AddRange(parsePoints(m->Groups["rest"]->Value, type));
		
	}
	else {
		throw gcnew ArgumentException(String::Format("Incorrect {0} properies: {1}", type, props));
	}

	return res;

}

GShapeParser::GShapeParser()
{
}

GShape^ GShapeParser::parse(String ^ str)
{
	// Line; -16777216; 1; {X = 223, Y = 94}; {X = 293, Y = 203}
	// Circle; -65536; 1; {X = 513, Y = 205}; {X = 437, Y = 253}
	// Ellipse; -16744193; 1; {X = 343, Y = 332}; 40; 20
	// Polygon; -16777216; 1; {X=351,Y=125};{X=211,Y=120};{X=182,Y=230};{X=289,Y=303};{X=272,Y=207};

	GShape^ res;
	
	Regex^ shapeRegex = gcnew Regex(
		"(?<type>Line|Circle|Ellipse|Polygon);(?<color>-?[0-9]{1,8});(?<depth>[0-9]+);(?<props>.+)"
	);

	Match^ m = shapeRegex->Match(str);

	if (m->Success) {

		String^ type = m->Groups["type"]->Value;
		String^ props = m->Groups["props"]->Value;

		if (type->Equals("Line")) {
			List<Point>^ points = parsePoints(props, type);
			if (points->Count != 2) {
				throw gcnew ArgumentException("Incorrect number of points in: " + str);
			}
			res = gcnew GLine(points[0], points[1]);
		}
		else if (type->Equals("Circle")) {
			List<Point>^ points = parsePoints(props, type);
			if (points->Count != 2) {
				throw gcnew ArgumentException("Incorrect number of points in: " + str);
			}
			res = gcnew GCircle(points[0], points[1]);
		}
		else if (type->Equals("Ellipse")) {
			res = parseEllipse(props);
		}
		else if (type->Equals("Polygon")) {
			List<Point>^ points = parsePoints(props, type);
			if (points->Count < 3) {
				throw gcnew ArgumentException("Incorrect number of points in: " + str);
			}
			res = gcnew GPolygon(points);
		}
		else {
			throw gcnew ArgumentException("Incorrect type of shape");
		}

		res->setColor(Color::FromArgb(Int32::Parse(m->Groups["color"]->Value)));
		res->setDepth(Int32::Parse(m->Groups["depth"]->Value));
	}
	else {
		throw gcnew ArgumentException("Incorrect data while parsing");
	}

	return res;
}
