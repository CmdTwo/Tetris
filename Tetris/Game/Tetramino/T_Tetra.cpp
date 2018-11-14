#include "T_Tetra.h"



T_Tetra::T_Tetra()
{
	_matrix = new bool*[3];

	SetDefaultMatrix();

	_height = 2;
	_wight = 3;
	_matrixSize = 3;
}


T_Tetra::~T_Tetra()
{
}

void T_Tetra::SetDefaultMatrix()
{
	for (unsigned int i = 0; i != _matrixSize; i++)
		delete[] _matrix[i];

	_matrix[0] = new bool[3]{ 0, 0, 0 };
	_matrix[1] = new bool[3]{ 1, 1, 1 };
	_matrix[2] = new bool[3]{ 0, 1, 0 };
}