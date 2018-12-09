#pragma once
#include "Area/GameArea.h"
#include "Area/NextSpawn.h"
#include "Area/InfoPanel.h"
#include "Area/GameOver.h"
#include "../Generic/KeyInput.h"
#include "Tetramino/Figure.h"

class Game
{
private:

	GameArea* _gameArea;
	NextSpawn* _nextSpawnArea;
	InfoPanel* _infoPanelArea;
	GameOver* _gameOverArea;

	KeyInput _keyInput;
	
	bool* isFigureFreeze;

	Figure* _currentFigure;
	Figure* _nextFigure;

	Figure* GenerateFigure();
	
public:

	Game();

	void Start();
	void LiveCircle();

	~Game();
};

