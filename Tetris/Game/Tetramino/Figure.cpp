#include "Figure.h"
#include <exception>
#include <algorithm>

Figure::Figure(Vector2D pos) : Figure(pos, Rotate::Left, false)
{

}

Figure::Figure(Vector2D pos, unsigned int rotateMode, bool isInvert)
{
	_pos = pos;
	_rotateMode = rotateMode;
	_isInvert = isInvert;
}

Figure::~Figure()
{
	for (unsigned int i = 0; i != _matrixSize; i++)
		delete[] _matrix[i];
	delete[] _matrix;
}

void Figure::Transposition() 
{
	Transposition(_matrix, _matrixSize);
	//for (unsigned int i = 0; i != _matrixSize; i++)
	//	for (unsigned int j = 0; j != i; j++)
	//		std::swap(_matrix[i][j], _matrix[j][i]);
}


void Figure::Transposition(bool** matrix, size_t size)
{
	for (size_t i = 0; i != size; i++)
		for (size_t j = 0; j != i; j++)
			std::swap(matrix[i][j], matrix[j][i]);
}

bool* Figure::GetFreeSpaceIter(bool onVerical)
{
	unsigned int sum = 0;
	if (onVerical)
	{
		for (size_t i = 0; i != _matrixSize; i++)
		{
			sum = 0;
			for (size_t j = 0; j != _matrixSize; j++)
			{
				sum += _matrix[j][i];
			}
			if (sum == 0)
				return _matrix[i];
		}
	}
	else
	{
		for (size_t i = 0; i != _matrixSize; i++)
		{
			sum = 0;
			for (size_t j = 0; j != _matrixSize; j++)
			{
				sum += _matrix[i][j];
			}
			if (sum == 0)
				return _matrix[i];
		}
	}
	return 0;
}

bool** Figure::GetTransposMatrix()
{
	bool** matrixClone = new bool*[_matrixSize];
	for (size_t i = 0; i != _matrixSize; i++)
	{
		matrixClone[i] = new bool[_matrixSize];
		std::copy(_matrix[i], _matrix[i] + _matrixSize, matrixClone[i]);
	}

	Transposition(matrixClone, _matrixSize);

	return matrixClone;
}

void Figure::Flip(bool vertical)
{
	unsigned int iterCount = _matrixSize / 2;

	if (vertical)
	{
		for (unsigned int i = 0; i != iterCount; i++)
		{
			for (unsigned int j = 0; j != _matrixSize; j++)
			{
				std::swap(_matrix[i][j], _matrix[i + (_matrixSize - iterCount)][j]);
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i != _matrixSize; i++)
		{
			for (unsigned int j = 0; j != iterCount; j++)
			{
				std::swap(_matrix[i][j], _matrix[i][j + (_matrixSize - iterCount)]);
			}
		}
	}
}

void Figure::Rotate()
{
	if (_rotateMode != Rotate::NonRotate)
	{
		if (++_rotateMode == Rotate::NonRotate)
			_rotateMode = Rotate::Left;

		SetDefaultMatrix();

		if (!_isInvert)
		{
			switch (_rotateMode)
			{
			case(Rotate::Left):
				return;
			case(Rotate::Up):
				Transposition();
				Flip(false);
				break;
			case(Rotate::Down):
				Transposition();
				Flip(true);
				break;
			case(Rotate::Right):
				Flip(true);
				Flip(false);
				break;
			default:
				throw std::exception("Wrong rotate mode");
				break;
			}
		}
		else
		{
			switch (_rotateMode)
			{
			case(Rotate::Left):
				Flip(true);
				Flip(false);
				break;
			case(Rotate::Up):
				Transposition();
				Flip(true);
				break;
			case(Rotate::Down):
				Transposition();
				Flip(false);
				break;
			case(Rotate::Right):
				return;
			default:
				throw std::exception("Wrong rotate mode");
				break;
			}
		}
	}
}

void Figure::SetDefaultRotateMode()
{
	if(!_isInvert)
		_rotateMode = Rotate::Left;
	else
		_rotateMode = Rotate::Right;
}

bool Figure::IsFreeSpaceArea(unsigned int* begin, unsigned int* end)
{
	unsigned int sum = 0;
	while (begin != end)
		sum += *begin++;
	return sum == 0;
}

const unsigned int Figure::GetMatrixSize()
{
	return _matrixSize;
}

const unsigned int Figure::GetFigureID()
{
	return _figureID;
}

bool** Figure::GetMatrix()
{
	return _matrix;
}

const Vector2D Figure::GetPos()
{
	return _pos;
}

void Figure::SetPos(const Vector2D& pos)
{
	_pos = Vector2D(pos);
}