#pragma once
#include "Figure.h"

class J_Tetra : public Figure
{
private:
	void SetDefaultMatrix() override;

public:
	J_Tetra(Vector2D, ConsoleManager::ConsoleColor);
	~J_Tetra();
};

