#include "GameArea.h"
#include <time.h>
#include <stdlib.h>
#include <numeric>
#include <iostream>
#include "Tetramino/L_Tetra.h"
#include "../Global/ConsoleManager.h"

GameArea::GameArea(const unsigned int height, const unsigned int wight, const Vector2D pos) : Area(height, wight, pos)
{
	srand(time(NULL));

	_border = Border(this, 1);

	_gameMatrix = new unsigned int*[MATRIX_H];

	for (unsigned int i = 0; i != MATRIX_H; i++)
	{
		_gameMatrix[i] = new unsigned int[MATRIX_W];
		for (unsigned int j = 0; j != MATRIX_W; j++)
		{
			_gameMatrix[i][j] = 0;
		}
	}
	_nextFigure = GenerateFigure();
	SpawnFigure();
}

Figure* GameArea::GenerateFigure()
{
	return new L_Tetra(Vector2D(0, 0));
}

GameArea::~GameArea()
{
	for (unsigned int i = 0; i != MATRIX_H; i++)
		delete[] _gameMatrix[i];
	delete[] _gameMatrix;

	delete _currentFigure;
	delete _nextFigure;
}

void GameArea::Show()
{	
	//ConsoleManager::SetGameConsoleMode();
	_border.DrawBorder();
	
	for (unsigned int i = 0; i != MATRIX_H; i++)
	{
		ConsoleManager::SetCursosPosition(_pos.X, _pos.Y + i);
		for (unsigned int j = 0; j != MATRIX_W; j++)
		{
			std::cout << (_gameMatrix[i][j] != 0 ? '\xDB' : ' ');
		}
		std::cout << std::endl;
	}
}

void GameArea::TryRotateFigure(Figure* figure)
{
	
}

bool GameArea::CheckColision(const unsigned int* oneBegin, const unsigned int* oneEnd, const unsigned int* twoBegin, const unsigned int* twoEnd, const unsigned int n)
{
	while (oneBegin != oneEnd && twoBegin != twoEnd)
	{
		if (*oneBegin + *twoBegin > n)
			return false;
		oneBegin++;
		twoBegin++;
	}
	return true;
}

void GameArea::MoveFigure(Figure* figure, bool onVerical, bool onPositiveSide)
{

}

void GameArea::TryMoveFigure(Figure* figure, bool onVerical, bool onPositiveSide)
{
	unsigned int size = figure->GetMatrixSize();

	unsigned int* firstSide = new unsigned int[size];
	unsigned int* secondSide = new unsigned int[size];

	const Vector2D pos = figure->GetPos();

	int figureOffset = (size - 1) * (onPositiveSide ? 1 : 0);
	int gameOffset;

	if (onVerical)
	{
		gameOffset = (figureOffset == 0) ? pos.Y - 1 : pos.Y + size;
		gameOffset = (gameOffset < 0) ? 0 : gameOffset;
		for (size_t i = 0; i != size; i++)
		{
			firstSide[i] = figure->GetMatrix()[figureOffset][i];
			secondSide[i] = _gameMatrix[gameOffset][i];
		}
	}
	else
	{
		gameOffset = (figureOffset == 0) ? pos.X - 1 : pos.X + size;
		gameOffset = (gameOffset < 0) ? 0 : gameOffset;
		for (size_t i = 0; i != size; i++)
		{
			firstSide[i] = figure->GetMatrix()[i][figureOffset];
			secondSide[i] = _gameMatrix[i][gameOffset];
		}
	}

	if (CheckColision(firstSide, firstSide + size, secondSide, secondSide + size, 1))
	{
		ClearFigure(figure);

		if (onVerical)
		{
			figure->SetPos(Vector2D(pos.X, pos.Y + (onPositiveSide ? 1 : -1)));
		}
		else
		{
			figure->SetPos(Vector2D(pos.X + (onPositiveSide ? 1 : -1), pos.Y));			
		}

		DrawFigure(figure);
	}	

	delete firstSide;
	delete secondSide;
}

bool GameArea::CheckSpawnArea()
{
	unsigned int sum = 0;	
	unsigned int mid = _wight / 2;
	unsigned int figureMid = _currentFigure->GetMatrixSize() / 2;

	for (size_t i = 0; i != _currentFigure->GetMatrixSize(); i++)
		std::accumulate(_gameMatrix[i] + (mid - figureMid), _gameMatrix[i] + (mid + figureMid), sum);

	return sum == 0;
}

void GameArea::DrawFigure(Figure* figure)
{
	for (unsigned int i = 0; i != figure->GetMatrixSize(); i++)
	{
		for (unsigned int j = 0; j != figure->GetMatrixSize(); j++)
		{
			if (figure->GetMatrix()[i][j])
			{
				_gameMatrix[figure->GetPos().Y + i][figure->GetPos().X + j] = _currentFigure->GetFigureID();
			}
		}
	}
}

void GameArea::ClearFigure(Figure* figure)
{
	for (unsigned int i = 0; i != figure->GetMatrixSize(); i++)
	{
		for (unsigned int j = 0; j != figure->GetMatrixSize(); j++)
		{
			if (figure->GetMatrix()[i][j])
			{
				_gameMatrix[figure->GetPos().Y + i][figure->GetPos().X + j] = 0;
			}
		}
	}
}

void GameArea::SpawnFigure()
{
	_currentFigure = _nextFigure;
	_nextFigure = GenerateFigure();

	if (CheckSpawnArea())
	{
		_currentFigure->SetPos(Vector2D(MATRIX_W / 2 - _currentFigure->GetMatrixSize() / 2, 0));
		DrawFigure(_currentFigure);
	}
}