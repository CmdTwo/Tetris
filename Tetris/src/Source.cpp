#include "..\Game\GameArea.h"
#include <iostream>

int main()
{
	GameArea gameArea(20, 10, Vector2D(30, 3));
	gameArea.Show();

	std::cin.get();
	return 0;
}