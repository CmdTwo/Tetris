#pragma once
#include "Figure.h"

class I_Tetra : public Figure
{
private:
	void SetDefaultMatrix() override;

public:
	I_Tetra(Vector2D);
	~I_Tetra();
};

