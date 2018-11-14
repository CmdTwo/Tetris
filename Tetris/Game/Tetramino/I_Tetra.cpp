#include "I_Tetra.h"



I_Tetra::I_Tetra()
{
	_matrix = new bool*[3];

	SetDefaultMatrix();

	_height = 3;
	_wight = 1;
	_matrixSize = 3;
}


I_Tetra::~I_Tetra()
{
}

void I_Tetra::SetDefaultMatrix()
{
	for (unsigned int i = 0; i != _matrixSize; i++)
		delete[] _matrix[i];

	_matrix[0] = new bool[3]{ 1, 0, 0 };
	_matrix[1] = new bool[3]{ 1, 0, 0 };
	_matrix[2] = new bool[3]{ 1, 0, 0 };
}