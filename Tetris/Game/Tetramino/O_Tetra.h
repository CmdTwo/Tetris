#pragma once
#include "Figure.h"

class O_Tetra : public Figure
{
private:
	void SetDefaultMatrix() override;

public:
	O_Tetra();
	~O_Tetra();
};

