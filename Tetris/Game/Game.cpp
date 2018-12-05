#include "Game.h"

#pragma region Tetramino includes

#include "Tetramino/I_Tetra.h"
#include "Tetramino/J_Tetra.h"
#include "Tetramino/L_Tetra.h"
#include "Tetramino/O_Tetra.h"
#include "Tetramino/S_Tetra.h"
#include "Tetramino/T_Tetra.h"
#include "Tetramino/Z_Tetra.h"

#pragma endregion


Game::Game()
{
	_gameArea = new GameArea(20, 10, Vector2D(30, 3));
	_nextSpawnArea = new NextSpawn(3, 3, Vector2D(50, 5));

	_keyInput = new KeyInput();

	isFigureFreeze = &_gameArea->GetIsFreeze();
}

void Game::Start()
{
	_gameArea->Show();
	_nextSpawnArea->Show();
	LiveCircle();
}

Figure* Game::GenerateFigure()
{
	switch (rand() % 7 + 1)
	{
		case(1): return new I_Tetra(Vector2D(0, 0));
		case(2): return new J_Tetra(Vector2D(0, 0));
		case(3): return new L_Tetra(Vector2D(0, 0));
		case(4): return new O_Tetra(Vector2D(0, 0));
		case(5): return new S_Tetra(Vector2D(0, 0));
		case(6): return new T_Tetra(Vector2D(0, 0));
		case(7): return new Z_Tetra(Vector2D(0, 0));
		default: throw std::exception("Invaild figure spawn id!"); break;
	}
}

void Game::LiveCircle()
{
	_currentFigure = GenerateFigure();
	_nextFigure = GenerateFigure();

	while (_gameArea->SpawnFigure(_currentFigure))
	{
		_nextSpawnArea->UpdateFigure(_nextFigure);

		while (!*isFigureFreeze)
		{
			switch (_keyInput->GetKeyInput())
			{
				case(KeyInput::LeftRow):
					_gameArea->TryMoveFigure(_currentFigure, false, false);
					break;
				case(KeyInput::DownRow):
					_gameArea->TryMoveFigure(_currentFigure, true, true);
					break;
				case(KeyInput::RightRow):
					_gameArea->TryMoveFigure(_currentFigure, false, true);
					break;
				case(KeyInput::R):
					_gameArea->TryRotateFigure(_currentFigure);
					break;
				default:				
					break;
			}
		}

		_currentFigure->~Figure();

		_currentFigure = _nextFigure;
		_nextFigure = GenerateFigure();		
	}
}

Game::~Game()
{
	delete _gameArea;
	delete _keyInput;
}
