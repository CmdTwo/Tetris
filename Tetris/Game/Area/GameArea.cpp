#include "GameArea.h"
#include <time.h>
#include <stdlib.h>
#include <numeric>
#include <iostream>

#include "../../Global/ConsoleManager.h"

GameArea::GameArea()
{

}

GameArea::GameArea(const unsigned int height, const unsigned int wight, const Vector2D pos) : Area(height, wight, pos)
{
	_height = height;
	_wight = wight;

	GAME_AREA_H = &_height;
	GAME_AREA_W = &_wight;

	GLOBAL_MATRIX_H = *GAME_AREA_H + 2;
	GLOBAL_MATRIX_W = *GAME_AREA_W + 2;

	srand(time(NULL));
	_border = Border(this, 1);

	_globalMatrix = new unsigned int*[GLOBAL_MATRIX_H];

	for (size_t i = 0; i != GLOBAL_MATRIX_H; i++)
	{
		_globalMatrix[i] = new unsigned int[GLOBAL_MATRIX_W];
		for (size_t j = 0; j != GLOBAL_MATRIX_W; j++)
		{
			//if(i == 0 || i == GLOBAL_MATRIX_H - 1)
			if (i == GLOBAL_MATRIX_H - 1)
				_globalMatrix[i][j] = 8;
			else if (j == 0 || j == GLOBAL_MATRIX_W - 1)
				_globalMatrix[i][j] = 9;
			else
				_globalMatrix[i][j] = 0;
		}
	}

	_gameMatrix = new unsigned int*[*GAME_AREA_H];

	for (size_t i = 0; i != *GAME_AREA_H; i++)
	{
		_gameMatrix[i] = _globalMatrix[i + 1] + 1;
	}	
}

GameArea::~GameArea()
{
	for (unsigned int i = 0; i != GLOBAL_MATRIX_H; i++)
		delete[] _globalMatrix[i];
	delete[] _globalMatrix;
}

void GameArea::Show()
{	
	_border.DrawBorder();
	
	//for (unsigned int i = 0; i != *GAME_AREA_H; i++)
	//{
	//	ConsoleManager::SetCursosPosition(_pos.X, _pos.Y + i);
	//	for (unsigned int j = 0; j != *GAME_AREA_W; j++)
	//	{
	//		std::cout << (_gameMatrix[i][j] != 0 ? '\xDB' : ' ');
	//		//std::cout << _gameMatrix[i][j] << ' ';
	//	}
	//	std::cout << std::endl;
	//}
}

void GameArea::TryRotateFigure(Figure* figure)
{
	size_t size = figure->GetMatrixSize();
	unsigned int** before = new unsigned int*[size];

	ClearFigure(figure);

	for (size_t i = 0; i != size; i++)
	{
		unsigned int* iter = _globalMatrix[i + figure->GetPos().Y] + figure->GetPos().X;
		before[i] = new unsigned int[3];
		std::copy(iter, iter + size, before[i]);
	}		


	figure->Rotate();
	//DrawFigure(figure);

	if (DetectRotateCollision(figure->GetMatrix(), before, size))
	{
		figure->Rotate(false); 
	}

	DrawFigure(figure);
	
	for (size_t i = 0; i != size; i++)
		delete[] before[i];
	delete[] before;
}

bool GameArea::DetectRotateCollision(bool** first, unsigned int** second, const size_t size)
{
	bool* firstBegin;
	unsigned int* secondBegin;
	for (size_t i = 0; i != size; i++)
	{
		firstBegin = first[i];
		secondBegin = second[i];

		while (firstBegin != first[i] + size && secondBegin != second[i] + size)
		{
			if (*secondBegin != 0 && *firstBegin + *secondBegin > *secondBegin)
			{
				return true;
			}
			firstBegin++;
			secondBegin++;
		}
	}
	return false;
}

//bool GameArea::DetectCollision(bool** first, unsigned int** second, size_t size)
//{
//	//bool* firstBegin;
//	//unsigned int* secondBegin;
//	for (size_t i = 0; i != size; i++)
//	{
//		if (DetectCollision(first[i], second[i], size))
//			return true;
//		/*firstBegin = first[i];
//		secondBegin = second[i];
//
//		while (firstBegin != first[i] + size && secondBegin != second[i] + size)
//		{
//			if (*firstBegin != 0 && *secondBegin != 0)
//			{
//				return true;
//			}
//			firstBegin++;
//			secondBegin++;
//		}*/
//	}
//	return false;
//}

//bool GameArea::DetectCollision(bool* first, unsigned int* second, size_t size)
//{
//	bool* firstBegin = first;
//	unsigned int* secondBegin = second;
//	while (firstBegin != first + size && secondBegin != second + size)
//	{
//		if (*firstBegin != 0 && *secondBegin != 0)
//		{
//			return true;
//		}
//		firstBegin++;
//		secondBegin++;
//	}
//	return false;
//}

bool GameArea::DetectBorderCollision(const unsigned int controlSum, const size_t size)
{
	return controlSum == MapElementID::border * size;
}

bool GameArea::DetectEndAreaCollision(const unsigned int controlSum, const size_t size)
{
	return controlSum == MapElementID::endArea * size;
}

void GameArea::TryMoveFigure(Figure* figure, bool onVertical, bool onPositiveSide)
{
	ClearFigure(figure);

	size_t size = figure->GetMatrixSize();
	Vector2D pos = figure->GetPos();

	unsigned int** nextPosMatrix = new unsigned int*[size];
	bool** figureMatrix = figure->GetMatrix();

	size_t posOffset;

	unsigned int controlSum = 0;

	if (onVertical)
	{
		posOffset = (onPositiveSide) ? pos.Y + 1 : pos.Y - 1;
		for (size_t i = 0; i != size; i++)
			nextPosMatrix[i] = _globalMatrix[posOffset + i] + pos.X;
	}
	else
	{
		posOffset = (onPositiveSide) ? pos.X + 1 : pos.X - 1;
		figureMatrix = figure->GetTransposMatrix();

		for (size_t i = 0; i != size; i++)
		{
			nextPosMatrix[i] = new unsigned int[size];
			for (size_t j = 0; j != size; j++)
				nextPosMatrix[i][j] = _globalMatrix[j + pos.Y][posOffset + i];
		}	
	}

	if (onPositiveSide)
		controlSum = GetControlSum(nextPosMatrix[size - 1], nextPosMatrix[size - 1] + size);
	else
		controlSum = GetControlSum(nextPosMatrix[0], nextPosMatrix[0] + size);

	if (DetectBorderCollision(controlSum, size)) // проверка коллизии с границей
	{
		bool detectLocalCollision = (onPositiveSide) ? DetectCollision(figureMatrix[size - 1], figureMatrix[size - 1] + size, size)
			: DetectCollision(figureMatrix[0], figureMatrix[0] + size, size);

		if (!detectLocalCollision && !DetectCollision(figureMatrix, nextPosMatrix, size)) // попытка локального сдвига
		{
			figure->LocalMove(onVertical, onPositiveSide);
		}
	}
	else if (DetectEndAreaCollision(controlSum, size)) // проверка коллизии с нижней границей
	{		
		bool detectLocalCollision = (onPositiveSide) ? DetectCollision(figureMatrix[size - 1], figureMatrix[size - 1] + size, size)
			: DetectCollision(figureMatrix[0], figureMatrix[0] + size, size);

		if (!detectLocalCollision && !DetectCollision(figureMatrix, nextPosMatrix, size)) // попытка локального сдвига
		{
			figure->LocalMove(onVertical, onPositiveSide);
		}
		else
		{
			isFreeze = true;
		}
	}
	else if (!DetectCollision(figureMatrix, nextPosMatrix, size)) // общая проверка коллизии
	{
		if (onVertical)
			figure->MoveOnY(onPositiveSide ? 1 : -1);
		else
			figure->MoveOnX(onPositiveSide ? 1 : -1);
	}
	else if (controlSum != 0) // проверка коллизии с фигурой
	{
		if(onVertical)
			isFreeze = true;
	}
	else //(DetectCollision(figureMatrix, nextPosMatrix, size)) // проверка локальной коллизии с фигурой
	{
		if(onVertical)
			isFreeze = true;
	}

	if (!onVertical)
	{
		for (size_t i = 0; i != size; i++)
			delete[] figureMatrix[i];
		delete[] figureMatrix;
	}

	delete[] nextPosMatrix;

	DrawFigure(figure);
}

bool GameArea::CheckSpawnArea(Figure* spawnFigure)
{
	unsigned int sum = 0;	
	unsigned int mid = *GAME_AREA_W / 2;
	unsigned int figureMid = spawnFigure->GetMatrixSize() / 2;

	for (size_t i = 0; i != spawnFigure->GetMatrixSize(); i++)
		sum += GetControlSum(_gameMatrix[i] + (mid - figureMid), _gameMatrix[i] + (mid + figureMid));

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
				ConsoleManager::SetCursosPosition(_pos.X + figure->GetPos().X + j - 1, _pos.Y + figure->GetPos().Y + i - 1);
				_globalMatrix[figure->GetPos().Y + i][figure->GetPos().X + j] = figure->GetColor();//figure->GetFigureID();
				
				ConsoleManager::SetConoleColor(figure->GetColor());
				std::cout << '\xDB';
				ConsoleManager::ResetColors();
			}
		}
	}
	ConsoleManager::SetCursosPosition(0, 0);
}

void GameArea::ClearFigure(Figure* figure)
{
	for (unsigned int i = 0; i != figure->GetMatrixSize(); i++)
	{
		for (unsigned int j = 0; j != figure->GetMatrixSize(); j++)
		{		
			if (figure->GetMatrix()[i][j])
			{
				ConsoleManager::SetCursosPosition(_pos.X + j + figure->GetPos().X - 1, _pos.Y + figure->GetPos().Y + i - 1);
				_globalMatrix[figure->GetPos().Y + i][figure->GetPos().X + j] = 0;
				std::cout << ' ';
			}
		}
	}
	ConsoleManager::SetCursosPosition(0, 0);
}

bool GameArea::SpawnFigure(Figure* figure)
{
	isFreeze = false;
	if (CheckSpawnArea(figure))
	{
		figure->SetPos(Vector2D(*GAME_AREA_W / 2 - figure->GetMatrixSize() / 2, 1));
		DrawFigure(figure);		
		return true;
	}
	else
	{
		return false;
	}	
}

bool& GameArea::GetIsFreeze()
{
	return isFreeze;
}

void GameArea::RemoveRow(size_t rowId)
{
	unsigned int* begin = _globalMatrix[rowId] + 1;
	unsigned int* end = _globalMatrix[rowId] + GLOBAL_MATRIX_W - 1;

	while (begin != end)
	{
		*begin = 0;
		begin++;
	}
}

void GameArea::ReShowArea()
{
	for (size_t i = 0; i != *GAME_AREA_H; i++)
	{
		ConsoleManager::SetCursosPosition(_pos.X, _pos.Y + i);
		for (size_t j = 0; j != *GAME_AREA_W; j++)
		{
			if (_gameMatrix[i][j] != 0)
			{
				ConsoleManager::SetConoleColor(static_cast<ConsoleManager::ConsoleColor>(_gameMatrix[i][j]));
				std::cout << '\xDB';
				ConsoleManager::ResetColors();
			}
			else
			{
				std::cout << ' ';
			}			
		}
		std::cout << std::endl;
	}
}

void GameArea::MoveDown(size_t beforeRowId)
{
	for (size_t i = beforeRowId; i != 0; i--)
	{
		for (size_t j = 1; j != GLOBAL_MATRIX_W - 1; j++)
		{
			std::swap(_globalMatrix[i - 1][j], _globalMatrix[i][j]);
		}
	}
}

std::vector<unsigned int> GameArea::GetScore(Figure* figure)
{
	std::vector<unsigned int> bonusIds;

	size_t chekedRows = 0;
	size_t size = figure->GetMatrixSize();

	Vector2D pos = figure->GetPos();


	while (chekedRows != size)
	{
		unsigned int posY = pos.Y + chekedRows;

		unsigned int* begin = _globalMatrix[posY] + 1;
		unsigned int* end = _globalMatrix[posY] + GLOBAL_MATRIX_W - 1;

		unsigned int constrolSum = GetControlSum(begin, end);

		if (constrolSum != 0)
		{
			bool isFull = true;
			unsigned int lastElement = 0;

			while (begin != end)
			{
				if (*begin == 0)
				{
					isFull = false;
					break;
				}
				lastElement = *begin;
				begin++;
			}

			if (isFull)
			{
				if (constrolSum / lastElement == lastElement)
					bonusIds.push_back(lastElement);
				else
					bonusIds.push_back(0);

				RemoveRow(posY);
				MoveDown(posY);
				ReShowArea();
			}
		}
		chekedRows++;
	}
	return bonusIds;
}