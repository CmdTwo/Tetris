#pragma once
#include "Figure.h"

class O_Tetra : public Figure
{
private:
	void SetDefaultMatrix() override;

public:
	O_Tetra(Vector2D, ConsoleManager::ConsoleColor color);
	~O_Tetra();
};

