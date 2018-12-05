#pragma once
#include "Area.h"
#include "..\Tetramino\Figure.h"
#include "..\..\Generic\Border.h"

class NextSpawn : public Area
{
private:
	Border _border;

public:
	NextSpawn(const unsigned int height, const unsigned int wight, const Vector2D pos);

	void Show();

	void UpdateFigure(Figure* figure);

	~NextSpawn();
};