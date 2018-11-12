#pragma once
#include "Vector2D.h"
#include "..\Game\Area.h"

class Border
{
private:
	Area* _obj;
	unsigned int _margin;

public:
	Border();

	Border(Area*, unsigned int);

	~Border();

	void DrawBorder();
};

