#include "InfoPanel.h"
#include "../../Global/ConsoleManager.h"
#include <iostream>

InfoPanel::InfoPanel(const unsigned int height, const unsigned int wight, const Vector2D pos) : Area(height, wight, pos)
{
	_border = Border(this, 1);

	_header = "Information:";

	_gameInfo.push_back("Score: 0");
	_gameInfo.push_back("Bonus: 0");

	_keysInfo.push_back("Move:   \x3C \x3E \x5E");
	_keysInfo.push_back("Rotate: R");
	_keysInfo.push_back("Exit:   Esc");
	_keysInfo.push_back("Help:   F1");
}


void InfoPanel::Show()
{
	_border.DrawBorder();

	ConsoleManager::SetCursosPosition(_pos.X + _header.size() / 3, _pos.Y);
	std::cout << _header.c_str() << std::endl;

	for (std::vector<std::string>::size_type i = 0; i != _gameInfo.size(); i++)
	{
		ConsoleManager::SetCursosPosition(_pos.X, _pos.Y + i + 2);
		std::cout << _gameInfo[i].c_str() << std::endl;
	}

	for (std::vector<std::string>::size_type i = 0; i != _keysInfo.size(); i++)
	{
		ConsoleManager::SetCursosPosition(_pos.X, _pos.Y + i + 5);
		std::cout << _keysInfo[i].c_str() << std::endl << std::endl;
	}
}

void InfoPanel::ResetBonus()
{
	ConsoleManager::SetCursosPosition(_pos.X + _gameInfo[1].size() - 1, _pos.Y + 3);
	std::cout << '0' << std::string(10, ' ').c_str();
}

void InfoPanel::UpdateBonus(unsigned int bonusScore)
{
	ConsoleManager::SetCursosPosition(_pos.X + _gameInfo[1].size() - 1, _pos.Y + 3);
	std::cout << '+' << bonusScore << std::string(10, ' ').c_str();
}

void InfoPanel::UpdateGameInfo(const std::vector<unsigned int> scoreVec)
{
	if (scoreVec.size() != 0)
	{
		ResetBonus();
		unsigned int bonus = 0;
		for (std::vector<unsigned int>::size_type i = 0; i != scoreVec.size(); i++)
		{
			_score++;

			if (scoreVec[i] != 0)
				bonus += scoreVec[i];
			bonus = i;
		}

		_score += bonus;

		if (bonus != 0)
			UpdateBonus(bonus);

		ConsoleManager::SetCursosPosition(_pos.X + _gameInfo[0].size() - 1, _pos.Y + 2);
		std::cout << _score << std::string(10, ' ').c_str();
	}
}

unsigned int InfoPanel::GetScore()
{
	return _score;
}

InfoPanel::~InfoPanel()
{
	_gameInfo.clear();
	_keysInfo.clear();
}
