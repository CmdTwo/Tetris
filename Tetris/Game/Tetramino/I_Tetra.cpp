#include "I_Tetra.h"



I_Tetra::I_Tetra(Vector2D pos, ConsoleManager::ConsoleColor color) : Figure(pos, color)
{
	_matrix = new bool*[3];

	SetDefaultMatrix();

	_height = 3;
	_wight = 1;
	_matrixSize = 3;
	//_figureID = 1;
}


I_Tetra::~I_Tetra()
{
}

void I_Tetra::SetDefaultMatrix()
{
	for (unsigned int i = 0; i != _matrixSize; i++)
		delete[] _matrix[i];

	_matrix[0] = new bool[3]{ 0, 1, 0 };
	_matrix[1] = new bool[3]{ 0, 1, 0 };
	_matrix[2] = new bool[3]{ 0, 1, 0 };
}