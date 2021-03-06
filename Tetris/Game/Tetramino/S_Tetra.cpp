#include "S_Tetra.h"



S_Tetra::S_Tetra(Vector2D pos, ConsoleManager::ConsoleColor color) : Figure(pos, Figure::Rotate::Right, true, color)
{
	_matrix = new bool*[3];

	SetDefaultMatrix();

	_height = 3;
	_wight = 2;
	_matrixSize = 3;
	//_figureID = 5;
}


S_Tetra::~S_Tetra()
{
}

void S_Tetra::SetDefaultMatrix()
{
	for (unsigned int i = 0; i != _matrixSize; i++)
		delete[] _matrix[i];

	_matrix[0] = new bool[3]{ 0, 0, 1 };
	_matrix[1] = new bool[3]{ 0, 1, 1 };
	_matrix[2] = new bool[3]{ 0, 1, 0 };
}