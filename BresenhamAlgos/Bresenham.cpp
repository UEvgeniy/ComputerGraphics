#include "Bresenham.h"
#include <math.h>

List<pair>^ Bresenham::buildLine(int x1, int y1, int x2, int y2)
{
	List<pair>^ res = gcnew List<pair>();

	int x = x1;
	int y = y1;

	// deltas
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	int s1 = sign(x2 - x1);
	int s2 = sign(y2 - y1); 

	// remember, if swapping x and y happened
	bool changed = false;
	if (dy > dx) {
		int tmp = dy;
		dy = dx;
		dx = tmp;
		changed = true;
	}

	// error
	int e = 2 * dy - dx;
	int i = 1;

	while (i <= dx) {

		res->Add(make_pair(x, y));

		while (e >= 0) {

			if (changed) { x += s1; }
			else { y += s2; }
			e -= 2 * dx;
		}

		if (changed) {
			y += s2;
		}
		else {
			x += s1;
		}

		e += 2 * dy;
		i++;
	}

	return res;
}

List<pair>^ Bresenham::buildCircle(int xc, int yc, int xk, int yk)
{
	List<pair>^ res = gcnew List<pair>();

	int x1 = xc;
	int x2 = xk;
	int y1 = yc;
	int y2 = yk;

	int dx = x1 - x2;
	int dy = y1 - y2;

	int x = 0;
	int y = sqrt(dx * dx + dy * dy);
	int d = 2 * (1 - y);
	int lim = 0;

	while (true) {

		res->Add(make_pair(x + x1, y + y1));
		res->Add(make_pair(x1 - x, y + y1));
		res->Add(make_pair(x + x1, y1 - y));
		res->Add(make_pair(x1 - x, y1 - y));

		if (y <= lim) {
			break;
		}

		if (d < 0) {
			if (2 * d + 2 * y - 1 <= 0) {
				x++;
				d += 2 * x + 1;
				continue;
			}
		}
		else if (d > 0) {
			if (2 * d - 2 * x - 1 > 0) {
				y--;
				d += -2 * y + 1;
				continue;
			}
		}
		x++;
		y--;
		d += 2 * x - 2 * y + 2;
	
	}

	return res;
}

List<pair>^ Bresenham::buildEllipse(int xc, int yc, int r1, int r2)
{
	List<pair>^ res = gcnew List<pair>();

	int x = 0;
	int y = r2;

	int h2 = r1* r1; // sqr of height
	int w2 = r2 * r2; // sqr of width
	int d = 4 * w2 * ((x + 1) * (x + 1)) + h2 * ((2 * y - 1) * (2 * y - 1)) - 4 * h2 * w2; // delta

	// when x increases every iter (y sometimes decreases)
	while (h2 * (2 * y - 1) > 2 * w2 * (x + 1)) {

		// reflect from the first quadrant to the rest
		res->Add(make_pair(xc + x, yc + y));
		res->Add(make_pair(xc + x, yc - y));
		res->Add(make_pair(xc - x, yc - y));
		res->Add(make_pair(xc - x, yc + y));

		if (d < 0) {
			x++;
			d += 4 * w2 * (2 * x + 3);
		}
		else {
			x++;
			d = d - 8 * h2 * (y - 1) + 4 * w2 * (2 * x + 3);
			y--;
		}
	}

	d = w2 * ((2 * x + 1) * (2 * x + 1)) + 4 * h2 * ((y + 1) * (y + 1)) - 4 * h2 * w2; 

	// when y decrease every iter (x sometimes increases)
	while (y + 1 != 0) 
	{
		// reflect from the first quadrant to the rest
		res->Add(make_pair(xc + x, yc + y));
		res->Add(make_pair(xc + x, yc - y));
		res->Add(make_pair(xc - x, yc - y));
		res->Add(make_pair(xc - x, yc + y));
		if (d < 0) 
		{
			y--;
			d += 4 * h2 * (2 * y + 3);
		}
		else 
		{
			y--;
			d = d - 8 * w2 * (x + 1) + 4 * h2 * (2 * y + 3);
			x++;
		}
	}

	return res;
}

pair Bresenham::make_pair(int x, int y)
{
	pair pp = gcnew array<int>(2);
	pp[0] = x;
	pp[1] = y;
	return pp;
}

// returns -1, 0 or	1 in dependence of value sign
int Bresenham::sign(int val)
{
	return (val > 0) ? (1) : ((val < 0) ? (-1) : (0));
}
