#include "NextSpawn.h"
#include <iostream>
#include "../../Global/ConsoleManager.h"

NextSpawn::NextSpawn(const unsigned int height, const unsigned int wight, const Vector2D pos) : Area(height, wight, pos)
{
	_border = Border(this, 1);
}

void NextSpawn::Show()
{
	_border.DrawBorder();
}

void NextSpawn::UpdateFigure(Figure* figure)
{
	size_t iterations = figure->GetMatrixSize() < _height ? figure->GetMatrixSize() : _height;

	for (size_t i = 0; i != _height; i++)
	{
		ConsoleManager::SetCursosPosition(_pos.X + figure->GetPos().X, _pos.Y + figure->GetPos().Y + i);
		std::cout << std::string(_wight, ' ').c_str();
	}

	for (size_t i = 0; i != iterations; i++)
	{
		for (size_t j = 0; j != iterations; j++)
		{
			ConsoleManager::SetCursosPosition(_pos.X + figure->GetPos().X + j, _pos.Y + figure->GetPos().Y + i);
			std::cout << (figure->GetMatrix()[i][j] != 0 ? '\xDB' : ' ');
		}
	}
}

NextSpawn::~NextSpawn()
{

}