#pragma once
#include "Area.h"
#include "..\Generic\Border.h"
#include "Tetramino/Figure.h"
#include <iostream>

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

	bool CheckSpawnArea();

	bool CheckColision(const unsigned int* oneBegin, const unsigned int* oneEnd, const unsigned int* twoBegin, const unsigned int* twoEnd, const unsigned int n);

	void MoveFigure(Figure* figure, bool onVerical, bool onPositiveSide);

	void DrawFigure(Figure*);

	void ClearFigure(Figure*);

public:	

	GameArea(const unsigned int, const unsigned int, const Vector2D);

	~GameArea();

	void TryRotateFigure(Figure*);

	void TryMoveFigure(Figure* figure, bool onVerical, bool onPositiveSide);

	void temp()
	{
		while (true)
		{
			Show();
			std::cin.get();
			TryMoveFigure(_currentFigure, true, false);
		}	
	}

	void SpawnFigure();

	void Show() override;
	
};

