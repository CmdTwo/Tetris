#pragma once
#include "Area.h"
#include "..\Generic\Border.h"

class GameArea : public Area
{
private:
	const unsigned int MATRIX_H = 20;
	const unsigned int MATRIX_W = 10;

	Border _border;
	unsigned int** gameMatrix;

public:
	GameArea(const unsigned int, const unsigned int, const Vector2D);

	~GameArea();

	void Show() override;
};

