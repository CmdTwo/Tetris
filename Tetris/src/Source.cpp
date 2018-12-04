#include "..\Game\GameArea.h"
#include "..\Game\Tetramino\Figure.h"
#include <iostream>

int** matrix;

const int size = 3;

void move(bool one, bool two)
{
	size_t iter = size - 1;

	if (one)
	{
		if (two)
		{

		}
	}
	else
	{
		if (two)
		{
			for (size_t i = 0; i != size; i++)
			{
				for (size_t j = iter; j != 0; j--)
				{
					std::swap(matrix[i][j], matrix[i][j - 1]);
				}
			}
		}
	}
}

void show()
{
	for (size_t i = 0; i != size; i++)
	{
		for (size_t j = 0; j != size; j++)
		{
			std::cout << matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

int main()
{
	GameArea gameArea(20, 10, Vector2D(30, 3));
	//gameArea.Show();
	gameArea.temp();
	
	//matrix = new int*[3];
	//matrix[0] = new int[3]{ 0, 1, 0 };
	//matrix[1] = new int[3]{ 0, 1, 0 };
	//matrix[2] = new int[3]{ 0, 1, 0 };

	//while (true)
	//{
	//	show();
	//	std::cin.get();
	//	move(false, true);
	//}
	return 0;
}