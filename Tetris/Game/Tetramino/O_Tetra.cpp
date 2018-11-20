#include "O_Tetra.h"



O_Tetra::O_Tetra(Vector2D pos) : Figure(pos, Figure::Rotate::NonRotate, false)
{
	_matrix = new bool*[2];

	SetDefaultMatrix();

	_height = 2;
	_wight = 2;
	_matrixSize = 2;
	_figureID = 4;
}


O_Tetra::~O_Tetra()
{
}

void O_Tetra::SetDefaultMatrix()
{
	for (unsigned int i = 0; i != _matrixSize; i++)
		delete[] _matrix[i];

	_matrix[0] = new bool[2]{ 1, 1 };
	_matrix[1] = new bool[2]{ 1, 1 };
}