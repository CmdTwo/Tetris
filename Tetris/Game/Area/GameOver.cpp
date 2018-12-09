#include "GameOver.h"
#include "../../Global/ConsoleManager.h"
#include <iostream>


GameOver::GameOver(const unsigned int height, const unsigned int wight, const Vector2D pos, InfoPanel* infoPanel) : Area(height, wight, pos)
{
	_infoPanel = infoPanel;
	_border = Border(this, 1);
}

void GameOver::Show()
{
	_border.DrawBorder();

	ConsoleManager::SetConoleColor(ConsoleManager::ConsoleColor::lightBlue);
	ConsoleManager::SetCursosPosition(_pos.X + _wight / 4, _pos.Y + 1);
	std::cout << "GAME OVER";
	ConsoleManager::SetCursosPosition(_pos.X + _wight / 4, _pos.Y + 3);
	std::cout << "Score: " << _infoPanel->GetScore();

	ConsoleManager::SetCursosPosition(0, 0);

	std::cin.get();
}

GameOver::~GameOver()
{
}
