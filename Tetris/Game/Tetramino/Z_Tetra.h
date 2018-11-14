#pragma once
#include "Figure.h"

class Z_Tetra :	public Figure
{
private:
	void SetDefaultMatrix() override;

public:
	Z_Tetra();
	~Z_Tetra();
};

