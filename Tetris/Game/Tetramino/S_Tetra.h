#pragma once
#include "Figure.h"

class S_Tetra : public Figure
{
private:
	void SetDefaultMatrix() override;

public:
	S_Tetra(Vector2D);
	~S_Tetra();
};

