#pragma once
#include "Figure.h"

class L_Tetra : public Figure
{
private:
	void SetDefaultMatrix() override;

public:

	L_Tetra(Vector2D, ConsoleManager::ConsoleColor);

	~L_Tetra();
};

