#pragma once
#include "../Generic/Vector2D.h"

class Area
{
protected:
	unsigned int _height;
	unsigned int _wight;
	Vector2D _pos;

public:
	Area(const unsigned int, const unsigned int, const Vector2D);

	~Area();

	virtual void Show() = 0;

	unsigned int GetHeight();
	unsigned int GetWight();
	Vector2D GetPos();
};

