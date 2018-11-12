#include "Border.h"
#include "..\Global\ConsoleManager.h"
#include <iostream>

Border::Border()
{

}

Border::Border(Area* area, unsigned int margin)
{
	_obj = area;
	_margin = margin;
}


Border::~Border()
{
}

void Border::DrawBorder()
{
	Vector2D drawPos = Vector2D(_obj->GetPos().X - _margin, _obj->GetPos().Y - _margin);

	ConsoleManager::SetCursosPosition(drawPos.X, drawPos.Y);
	std::cout << '\xDA' << std::string(_obj->GetWight(), '\xC4').c_str() << '\xBF';

	drawPos.Y += 1;

	for (unsigned int i = 0; i < _obj->GetHeight(); i++)
	{
		ConsoleManager::SetCursosPosition(drawPos.X, drawPos.Y + i);
		std::cout << '\xB3' << std::string(_obj->GetWight(), ' ').c_str() << '\xB3';
	}

	ConsoleManager::SetCursosPosition(drawPos.X, drawPos.Y + _obj->GetHeight());
	std::cout << '\xC0' << std::string(_obj->GetWight(), '\xC4').c_str() << '\xD9';
}
