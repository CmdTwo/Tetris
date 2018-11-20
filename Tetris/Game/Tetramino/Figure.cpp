#include "Figure.h"
#include <exception>
#include <algorithm>

Figure::Figure() : Figure(Vector2D(0, 0))
{
	
}

Figure::Figure(Vector2D pos)
{
	_isInvert = false;
	_rotateMode = Rotate::Left;
	_pos = pos;
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
	for (unsigned int i = 0; i != _matrixSize; i++)
		for (unsigned int j = 0; j != i; j++)
			std::swap(_matrix[i][j], _matrix[j][i]);
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