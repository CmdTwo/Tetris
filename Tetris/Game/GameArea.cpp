#include "GameArea.h"
#include <time.h>
#include <stdlib.h>
#include "Tetramino/O_Tetra.h"

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

	_currentFigure = GenerateFigure();

	_currentFigure->Show();

	_currentFigure->Rotate();
	_currentFigure->Show();

	_currentFigure->Rotate();
	_currentFigure->Show();

	_currentFigure->Rotate();
	_currentFigure->Show();

	//_currentFigure->Rotate();
	//_currentFigure->Show();

	//_currentFigure->Rotate();
	//_currentFigure->Show();

	_nextFigure = GenerateFigure();
}


Figure* GameArea::GenerateFigure()
{
	return new O_Tetra();
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
	_border.DrawBorder();

	for (unsigned int i = 0; i != MATRIX_H; i++)
	{
		for (unsigned int j = 0; j != MATRIX_W; j++)
		{
			if (_gameMatrix[i][j] != 0)
			{
				//switch (switch_on)
				//{
				//default:
				//	break;
				//}
			}
		}
	}
}

void GameArea::TryRotateFigure(Figure* figure)
{

}