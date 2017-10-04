#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

delegate void IterationDel(bool needShapesRedraw);

ref class Filling
{
protected:
	Bitmap^ _bm;
	Color _color;
public:
	event IterationDel^ onIteration;

	Filling(Bitmap^ bm, Color col);

	virtual void fill() = 0; // must be overriden in derived classes


	~Filling();
};

