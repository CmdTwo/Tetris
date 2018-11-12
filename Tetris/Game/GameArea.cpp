#include "GameArea.h"


GameArea::GameArea(const unsigned int height, const unsigned int wight, const Vector2D pos) : Area(height, wight, pos)
{
	_border = Border(this, 1);

	gameMatrix = new unsigned int*[MATRIX_H];

	for (unsigned int i = 0; i != MATRIX_H; i++)
	{
		gameMatrix[i] = new unsigned int[MATRIX_W];

		for (unsigned int j = 0; j != MATRIX_W; j++)
		{
			gameMatrix[i][j] = 0;
		}
	}
}


GameArea::~GameArea()
{
}

void GameArea::Show()
{
	_border.DrawBorder();
}