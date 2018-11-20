#include "..\Game\GameArea.h"
#include "..\Game\Tetramino\Figure.h"
#include <iostream>

int main()
{
	GameArea gameArea(20, 10, Vector2D(30, 3));
	//gameArea.Show();
	gameArea.temp();
	
	std::cin.get();
	return 0;
}