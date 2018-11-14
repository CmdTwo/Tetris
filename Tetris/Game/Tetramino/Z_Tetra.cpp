#include "Z_Tetra.h"



Z_Tetra::Z_Tetra()
{
	_matrix = new bool*[3];

	SetDefaultMatrix();

	_height = 3;
	_wight = 2;
	_matrixSize = 3;
}


Z_Tetra::~Z_Tetra()
{
}

void Z_Tetra::SetDefaultMatrix()
{
	for (unsigned int i = 0; i != _matrixSize; i++)
		delete[] _matrix[i];

	_matrix[0] = new bool[3]{ 1, 0, 0 };
	_matrix[1] = new bool[3]{ 1, 1, 0 };
	_matrix[2] = new bool[3]{ 0, 1, 0 };
}