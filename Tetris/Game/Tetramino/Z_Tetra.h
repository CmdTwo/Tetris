#pragma once
#include "Figure.h"

class Z_Tetra :	public Figure
{
private:
	void SetDefaultMatrix() override;

public:
	Z_Tetra(Vector2D);
	~Z_Tetra();
};

