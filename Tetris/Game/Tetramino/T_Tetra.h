#pragma once
#include "Figure.h"

class T_Tetra : public Figure
{
private:
	void SetDefaultMatrix() override;

public:
	T_Tetra(Vector2D, ConsoleManager::ConsoleColor);
	~T_Tetra();
};

