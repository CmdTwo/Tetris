#pragma once
#include "Area.h"
#include "..\..\Generic\Border.h"
#include <vector>

class InfoPanel : public Area
{
private:
	Border _border;

	std::string _header;

	std::vector<std::string> _gameInfo;
	std::vector<std::string> _keysInfo;

	unsigned int _score;

	void UpdateBonus(unsigned int bonusScore);

	void ResetBonus();

public:
	InfoPanel(const unsigned int height, const unsigned int wight, const Vector2D pos);

	void Show();

	void UpdateGameInfo(const std::vector<unsigned int> scoreVec);

	unsigned int GetScore();

	~InfoPanel();
};

