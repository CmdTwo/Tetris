#include "J_Tetra.h"



J_Tetra::J_Tetra(Vector2D pos) : Figure(pos, Figure::Rotate::Right, true)
{
	_matrix = new bool*[3];

	SetDefaultMatrix();

	_height = 3;
	_wight = 2;
	_matrixSize = 3;
	_figureID = 2;
}


J_Tetra::~J_Tetra()
{

}

void J_Tetra::SetDefaultMatrix()
{
	for (unsigned int i = 0; i != _matrixSize; i++)
		delete[] _matrix[i];

	_matrix[0] = new bool[3]{ 0, 1, 0 };
	_matrix[1] = new bool[3]{ 0, 1, 0 };
	_matrix[2] = new bool[3]{ 1, 1, 0 };
}
