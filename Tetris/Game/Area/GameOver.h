#pragma once
#include "Area.h"
#include "..\..\Generic\Border.h"
#include "InfoPanel.h"

class GameOver : public Area
{
private:
	Border _border;
	InfoPanel* _infoPanel;

public:
	GameOver(const unsigned int height, const unsigned int wight, const Vector2D pos, InfoPanel*);

	void Show();

	~GameOver();
};

