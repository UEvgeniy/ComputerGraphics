#include "Bresenham.h"
#include <math.h>

List<pair>^ Bresenham::buildLine(int x1, int y1, int x2, int y2)
{
	List<pair>^ res = gcnew List<pair>();

	int x = x1;
	int y = y1;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	int s1 = sign(x2 - x1);
	int s2 = sign(y2 - y1); 

	bool changed = false;
	if (dy > dx) {
		int tmp = dy;
		dy = dx;
		dx = tmp;
		changed = true;
	}

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

	int a = 0;
	int b = r2;

	int h2 = r1* r1;
	int w2 = r2 * r2;
	int d = 4 * w2 * ((a + 1) * (a + 1)) + h2 * ((2 * b - 1) * (2 * b - 1)) - 4 * h2 * w2;

	while (h2 * (2 * b - 1) > 2 * w2 * (a + 1)) {

		res->Add(make_pair(xc + a, yc + b));
		res->Add(make_pair(xc + a, yc - b));
		res->Add(make_pair(xc - a, yc - b));
		res->Add(make_pair(xc - a, yc + b));

		if (d < 0) {
			a++;
			d += 4 * w2 * (2 * a + 3);
		}
		else {
			a++;
			d = d - 8 * h2 * (b - 1) + 4 * w2 * (2 * a + 3);
			b--;
		}
	}

	d = w2 * ((2 * a + 1) * (2 * a + 1)) + 4 * h2 * ((b + 1) * (b + 1)) - 4 * h2 * w2; 

	while (b + 1 != 0) 
	{

		res->Add(make_pair(xc + a, yc + b));
		res->Add(make_pair(xc + a, yc - b));
		res->Add(make_pair(xc - a, yc - b));
		res->Add(make_pair(xc - a, yc + b));
		if (d < 0) 
		{
			b--;
			d += 4 * h2 * (2 * b + 3);
		}
		else 
		{
			b--;
			d = d - 8 * w2 * (a + 1) + 4 * h2 * (2 * b + 3);
			a++;
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

int Bresenham::sign(int val)
{
	return (val > 0) ? (1) : ((val < 0) ? (-1) : (0));
}
