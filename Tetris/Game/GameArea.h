#pragma once
#include "Area.h"
#include "..\Generic\Border.h"
#include "Tetramino/Figure.h"
#include <iostream>
#include "..\Generic\KeyInput.h"

class GameArea : public Area
{
private:
	
	enum MapElementID : unsigned int {
		border = 9,
		endArea = 8,
	};
	
	const unsigned int GLOBAL_MATRIX_H = 22;
	const unsigned int GLOBAL_MATRIX_W = 12;
	const unsigned int GAME_AREA_H = 20;
	const unsigned int GAME_AREA_W = 10;

	Figure* _currentFigure;
	Figure* _nextFigure;

	Border _border;
	unsigned int** _globalMatrix;
	unsigned int** _gameMatrix;

	Figure* GenerateFigure();

	bool CheckSpawnArea();

	bool CheckCollision(const unsigned int* oneBegin, const unsigned int* oneEnd, const unsigned int* twoBegin, const unsigned int* twoEnd, const unsigned int n);

	bool DetectCollision(bool** first, unsigned int** second, const size_t size);

	bool DetectBorderCollision(const unsigned int controlSum, const size_t size);

	bool DetectEndAreaCollision(const unsigned int controlSum, const size_t size);
	
	unsigned int GetControlSum(unsigned int* begin, unsigned int* end);

	inline bool CheckOutBorder(Vector2D pos, unsigned int size);

	void DrawFigure(Figure*);

	void ClearFigure(Figure*);

public:	

	GameArea(const unsigned int, const unsigned int, const Vector2D);

	~GameArea();

	void TryRotateFigure(Figure*);

	void TryMoveFigure(Figure* figure, bool onVerical, bool onPositiveSide);

	void temp()
	{
		_nextFigure = GenerateFigure();
		SpawnFigure();

		KeyInput keys;

		Show();

		while (true)
		{
		/*	Show();*/
			//std::cin.get();
			//ClearFigure(_currentFigure);
			//_currentFigure->LocalMove(false, true);
			//DrawFigure(_currentFigure);


			switch (keys.GetKeyInput())
			{
			case(KeyInput::UpRow):
				TryMoveFigure(_currentFigure, true, false);
				break;
			case(KeyInput::LeftRow):
				TryMoveFigure(_currentFigure, false, false);
				break;
			case(KeyInput::DownRow):
				TryMoveFigure(_currentFigure, true, true);
				break;
			case(KeyInput::RightRow):
				TryMoveFigure(_currentFigure, false, true);
				break;
			case(KeyInput::NonGameKey):
				TryRotateFigure(_currentFigure);
				break;
			default:
				break;
			}			
		}	
	}

	void SpawnFigure();

	void Show() override;
	
};

