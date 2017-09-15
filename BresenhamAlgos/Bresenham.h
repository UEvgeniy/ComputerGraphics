#pragma once

using namespace std;
using namespace System::Collections::Generic;

typedef array<int>^ pair;

public class Bresenham {

	public:
		
		static List<pair>^ buildLine(int x1, int y1, int x2, int y2);

		static List<pair>^ buildCircle(int xc, int yc, int x2, int y2);

		static List<pair>^ buildEllipse(int xc, int yc, int r1, int r2);

private:
	static pair make_pair(int x, int y);
	static int sign(int val);
};
