#include "GameArea.h"
#include <time.h>
#include <stdlib.h>
#include <numeric>
#include <iostream>

#include "Tetramino/I_Tetra.h"
#include "Tetramino/J_Tetra.h"
#include "Tetramino/L_Tetra.h"
#include "Tetramino/O_Tetra.h"
#include "Tetramino/S_Tetra.h"
#include "Tetramino/T_Tetra.h"
#include "Tetramino/Z_Tetra.h"

#include "../Global/ConsoleManager.h"

GameArea::GameArea(const unsigned int height, const unsigned int wight, const Vector2D pos) : Area(height, wight, pos)
{
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

			if(i == 5 && j >= 3 && j <= 5)
				_globalMatrix[i][j] = 7;
		}
	}

	_gameMatrix = new unsigned int*[GAME_AREA_H];

	for (size_t i = 0; i != GAME_AREA_H; i++)
	{
		_gameMatrix[i] = _globalMatrix[i + 1] + 1;
	}

	//*_gameMatrix = new unsigned int*[MATRIX_H];

	//for (unsigned int i = 0; i != MATRIX_H; i++)
	//{
	//	_gameMatrix[i] = new unsigned int[MATRIX_W];
	//	for (unsigned int j = 0; j != MATRIX_W; j++)
	//	{
	//		_gameMatrix[i][j] = 0;
	//	}
	//}*/

	//_nextFigure = GenerateFigure();
	//SpawnFigure();
}

/*
	0 0 0 0 0 0 0 0 0
	0 0 0 1 1 0 0 0 0
	0 0 0 1 2 0 0 0 0
	0 0 0 1 2 0 0 0 0
	0 0 0 0 2 0 0 0 0
	0 0 0 0 0 0 0 0 0
*/

Figure* GameArea::GenerateFigure()
{
	//switch (rand() % 7 + 1)
	//{
	//case(1): return new I_Tetra(Vector2D(0, 0));
	//case(2): return new J_Tetra(Vector2D(0, 0));
	//case(3): return new L_Tetra(Vector2D(0, 0));
	//case(4): return new O_Tetra(Vector2D(0, 0));
	//case(5): return new S_Tetra(Vector2D(0, 0));
	//case(6): return new T_Tetra(Vector2D(0, 0));
	//case(7): return new Z_Tetra(Vector2D(0, 0));
	//default: throw std::exception("Invaild figure spawn id!"); break;
	//}
	return new L_Tetra(Vector2D(0, 0));
}

GameArea::~GameArea()
{
	for (unsigned int i = 0; i != GLOBAL_MATRIX_H; i++)
		delete[] _globalMatrix[i];
	delete[] _globalMatrix;

	delete _currentFigure;
	delete _nextFigure;
}

void GameArea::Show()
{	
	//ConsoleManager::SetGameConsoleMode();
	//_border.DrawBorder();
	
	for (unsigned int i = 0; i != GAME_AREA_H; i++)
	{
		ConsoleManager::SetCursosPosition(_pos.X, _pos.Y + i);
		for (unsigned int j = 0; j != GAME_AREA_W; j++)
		{
			//std::cout << (_gameMatrix[i][j] != 0 ? '\xDB' : ' ');
			std::cout << _gameMatrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void GameArea::TryRotateFigure(Figure* figure)
{

}

bool GameArea::CheckOutBorder(Vector2D pos, unsigned int size)
{
	return pos.X < -1 || pos.X + size - 1 > GAME_AREA_W || pos.Y < -1 || pos.Y + size - 1 > GAME_AREA_H;
}

/*bool GameArea::CheckCollision(const unsigned int* oneBegin, const unsigned int* oneEnd, const unsigned int* twoBegin, const unsigned int* twoEnd, const unsigned int n)
{
	while (oneBegin != oneEnd && twoBegin != twoEnd)
	{
		if (*oneBegin + *twoBegin > n)
			return false;
		oneBegin++;
		twoBegin++;
	}
	return true;
}*/

bool GameArea::DetectCollision(bool** first, unsigned int** second, size_t size)
{
	bool* firstBegin;
	unsigned int* secondBegin;
	for (size_t i = 0; i != size; i++)
	{
		firstBegin = first[i];
		secondBegin = second[i];

		while (firstBegin != first[i] + size && secondBegin != second[i] + size)
		{
			if (*firstBegin != 0 && *secondBegin != 0)
			{
				return true;
			}
			firstBegin++;
			secondBegin++;
		}
	}
	return false;
}

bool GameArea::DetectBorderCollision(const unsigned int controlSum, const size_t size)
{
	return controlSum == MapElementID::border * size;
}

bool GameArea::DetectEndAreaCollision(const unsigned int controlSum, const size_t size)
{
	return controlSum == MapElementID::endArea * size;
}

unsigned int GameArea::GetControlSum(unsigned int* begin, unsigned int* end)
{
	unsigned int sum = 0;
	while (begin != end)
		sum += *begin++;
	return sum;
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

	if (DetectBorderCollision(controlSum, size)) // проверка коллизии с раницей
	{
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << std::string(40, ' ').c_str() << std::endl;
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << "Detect the border collision";
	} 
	else if (!DetectCollision(figureMatrix, nextPosMatrix, size)) // общая проверка коллизии
	{
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << std::string(40, ' ').c_str() << std::endl;
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << "No detected any collision";

		if (onVertical)
			figure->SetPos(Vector2D(pos.X, pos.Y + (onPositiveSide ? 1 : -1)));
		else
			figure->SetPos(Vector2D(pos.X + (onPositiveSide ? 1 : -1), pos.Y));
	}
	else if (DetectEndAreaCollision(controlSum, size)) // проверка коллизии с нижней границей
	{
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << std::string(40, ' ').c_str() << std::endl;
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << "Detect the end area collision";
	}
	else if (controlSum != 0) // проверка коллизии с фигурой
	{
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << std::string(40, ' ').c_str() << std::endl;
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << "Detect the figure collision";
	}
	else if (!DetectCollision(figureMatrix, nextPosMatrix, size - 1)) // проверка локальной коллизии с фигурой
	{
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << std::string(40, ' ').c_str() << std::endl;
		ConsoleManager::SetCursosPosition(0, 0);
		std::cout << "Detect the local figure collision";
	}

	DrawFigure(figure);
	Show();
}

//void GameArea::TryMoveFigure(Figure* figure, bool onVerical, bool onPositiveSide)
//{
//	unsigned int size = figure->GetMatrixSize();
//
//	unsigned int* firstSide = new unsigned int[size];
//	unsigned int* secondSide = new unsigned int[size];
//
//	const Vector2D pos = figure->GetPos();
//		
//	int figureOffset = (size - 1) * (onPositiveSide ? 1 : 0);
//	int gameOffset;
//	bool isFreeSpace = false;
//
//	if (onVerical)
//	{
//		for (size_t i = 0; i != size; i++)
//			firstSide[i] = figure->GetMatrix()[figureOffset][i];
//
//		bool isFree = figure->IsFreeSpaceArea(firstSide, firstSide + size);
//
//		if (onPositiveSide && pos.Y != 18 && (pos.Y != GAME_AREA_H - size || (pos.Y != GAME_AREA_H - size - 1 && isFree)))
//		{
//			gameOffset = (pos.Y + size == GAME_AREA_H && isFree) ? pos.Y + size - 1: pos.Y + size;
//			for (size_t i = 0; i != size; i++)
//				secondSide[i] = _gameMatrix[gameOffset][i];
//		}
//		else if (!onPositiveSide && pos.Y != 0)
//		{
//			gameOffset = pos.Y - 1;
//			for (size_t i = 0; i != size; i++)
//				secondSide[i] = _gameMatrix[gameOffset][i];
//		}
//	}
//	else
//	{
//		for (size_t i = 0; i != size; i++)
//			firstSide[i] = figure->GetMatrix()[i][figureOffset];
//
//		bool temp = figure->IsFreeSpaceArea(firstSide, firstSide + size);
//
//		if (!onPositiveSide && pos.X != -1)
//		{
//			gameOffset = (pos.X - 1 < 0 && temp) ? 0 : pos.X - 1;
//			for (size_t i = 0; i != size; i++)
//				secondSide[i] = _gameMatrix[i][gameOffset];
//		}
//		else if (onPositiveSide && pos.X != GAME_AREA_W + 1 - size)
//		{
//			gameOffset = (pos.X + size == GAME_AREA_W && temp ? pos.X + size - 1 : pos.X + size);
//			for (size_t i = 0; i != size; i++)
//				secondSide[i] = _gameMatrix[i][gameOffset];			
//		}
//	}
//
//	if (CheckCollision(firstSide, firstSide + size, secondSide, secondSide + size, 1))
//	{
//		ClearFigure(figure);
//
//		if (onVerical)
//			figure->SetPos(Vector2D(pos.X, pos.Y + (onPositiveSide ? 1 : -1)));
//		else
//			figure->SetPos(Vector2D(pos.X + (onPositiveSide ? 1 : -1), pos.Y));
//
//		DrawFigure(figure);
//	}
//
//	delete firstSide;
//	delete secondSide;
//}

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
				//ConsoleManager::SetCursosPosition(_pos.X + figure->GetPos().X + j, _pos.Y + figure->GetPos().Y + i);
				_globalMatrix[figure->GetPos().Y + i][figure->GetPos().X + j] = _currentFigure->GetFigureID();
				//std::cout << '\xDB';
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
				//ConsoleManager::SetCursosPosition(_pos.X + j + figure->GetPos().X, _pos.Y + figure->GetPos().Y + i);
				_globalMatrix[figure->GetPos().Y + i][figure->GetPos().X + j] = 0;
				//std::cout << ' ';
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
		_currentFigure->SetPos(Vector2D(GAME_AREA_W / 2 - _currentFigure->GetMatrixSize() / 2, 1));
		DrawFigure(_currentFigure);
	}
}