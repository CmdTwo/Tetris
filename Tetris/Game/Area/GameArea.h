#pragma once
#include "Area.h"
#include "..\..\Generic\Border.h"
#include "..\Tetramino/Figure.h"
#include <iostream>

class GameArea : public Area
{
private:
	
	enum MapElementID : unsigned int {
		border = 9,
		endArea = 8,
	};
	
	bool isFreeze;

	unsigned int GLOBAL_MATRIX_H;
	unsigned int GLOBAL_MATRIX_W;
	unsigned int* GAME_AREA_H;
	unsigned int* GAME_AREA_W;

	Border _border;
	unsigned int** _globalMatrix;
	unsigned int** _gameMatrix;

	bool CheckSpawnArea(Figure* spawnFigure);

	bool DetectRotateCollision(bool** first, unsigned int** second, const size_t size);

	template<class One, class Two>
	bool DetectCollision(One** first, Two** second, const size_t size)
	{
		for (size_t i = 0; i != size; i++)
		{
			if (DetectCollision(first[i], second[i], size))
				return true;
		}
		return false;
	}

	template<class One, class Two>
	bool DetectCollision(One* first, Two* second, const size_t size)
	{
		One* firstBegin = first;
		Two* secondBegin = second;
		while (firstBegin != first + size && secondBegin != second + size)
		{
			if (*firstBegin != 0 && *secondBegin != 0)
			{
				return true;
			}
			firstBegin++;
			secondBegin++;
		}
		return false;
	}

	bool DetectBorderCollision(const unsigned int controlSum, const size_t size);

	bool DetectEndAreaCollision(const unsigned int controlSum, const size_t size);
	
	template<class One, class Two>
	unsigned int GetControlSum(One* begin, Two* end)
	{
		unsigned int sum = 0;
		while (begin != end)
			sum += *begin++;
		return sum;
	}

	template<class One, class Two>
	unsigned int GetMatrixConstrolSum(One** firstMatrix, Two** secondMatrix, size_t size)
	{
		unsigned int sum = 0;
		for (size_t i = 0; i != size; i++)
		{
			for (size_t j = 0; j != size; j++)
			{
				sum += firstMatrix[i][j] + secondMatrix[i][j];
			}
		}
		return sum;
	}

	void DrawFigure(Figure*);

	void ClearFigure(Figure*);

public:	

	GameArea();

	GameArea(const unsigned int, const unsigned int, const Vector2D);

	~GameArea();

	void TryRotateFigure(Figure*);

	void TryMoveFigure(Figure* figure, bool onVerical, bool onPositiveSide);

	bool SpawnFigure(Figure* figure);

	void Show() override;

	bool& GetIsFreeze();	
};

