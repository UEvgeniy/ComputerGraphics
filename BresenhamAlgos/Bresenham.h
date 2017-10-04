#pragma once

using namespace System;
using namespace System::Collections::Generic;


//typedef array<int>^ pair;

Tuple<int, int>^ make_pair(int x, int y);

public class Bresenham {

	public:
		
		static List<Tuple<int, int>^>^ buildLine(int x1, int y1, int x2, int y2);

		static List<Tuple<int, int>^>^ buildCircle(int xc, int yc, int x2, int y2);

		static List<Tuple<int, int>^>^ buildEllipse(int xc, int yc, int r1, int r2);

private:
	static int sign(int val);
};
