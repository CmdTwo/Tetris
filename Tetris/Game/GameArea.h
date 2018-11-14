#pragma once
#include "Area.h"
#include "..\Generic\Border.h"
#include "Tetramino/Figure.h"

class GameArea : public Area
{
private:
	const unsigned int MATRIX_H = 20;
	const unsigned int MATRIX_W = 10;

	Figure* _currentFigure;
	Figure* _nextFigure;

	Border _border;
	unsigned int** _gameMatrix;

	Figure* GenerateFigure();

public:
	GameArea(const unsigned int, const unsigned int, const Vector2D);

	~GameArea();

	void Show() override;

	void TryRotateFigure(Figure*);
};

