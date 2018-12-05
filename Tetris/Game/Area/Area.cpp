#include "Area.h"

Area::Area()
{

}

Area::Area(const unsigned int height, const unsigned int wight, const Vector2D pos)
{
	_height = height;
	_wight = wight;
	_pos = pos;
}


Area::~Area()
{
}

unsigned int Area::GetHeight()
{
	return _height;
}

unsigned int Area::GetWight()
{
	return _wight;
}

Vector2D Area::GetPos()
{
	return _pos;
}
