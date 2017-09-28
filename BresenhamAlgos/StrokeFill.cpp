#include "StrokeFill.h"



StrokeFill::StrokeFill(Color col, Point^ seed) : GShape(col, 1)
{
	this->_seed = seed;
}

List<pair>^ StrokeFill::getPixels()
{
	List<pair>^ res = gcnew List<pair>();

	for (int i = 0; i < 10; i++) {
		res->Add(make_pair(_seed->X + i, _seed->Y + i));
		res->Add(make_pair(_seed->X - i, _seed->Y + i));
		res->Add(make_pair(_seed->X + i, _seed->Y - i));
		res->Add(make_pair(_seed->X - i, _seed->Y - i));
	}


	return res;
}

System::String ^ StrokeFill::ToString()
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}
