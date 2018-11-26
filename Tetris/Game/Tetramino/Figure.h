#pragma once
#include "../../Generic/Vector2D.h"

class Figure
{
public:
	enum Rotate
	{
		Left,
		Down,
		Right,
		Up,
		NonRotate
	};

protected:
	bool** _matrix;
	bool _isInvert;

	unsigned int _matrixSize;
	unsigned int _figureID;
	unsigned int _rotateMode;
	unsigned int _height;
	unsigned int _wight;

	Figure(Vector2D, unsigned int, bool);

private:
	Vector2D _pos;

	void Transposition();

	void Transposition(bool** matrix, size_t size);

	void Flip(bool);

	virtual void SetDefaultMatrix() = 0;

	virtual void SetDefaultRotateMode();

public:

	Figure(Vector2D);

	~Figure();

	void Rotate();

	bool IsFreeSpaceArea(unsigned int* begin, unsigned int* end);

	bool* GetFreeSpaceIter(bool onVerical);

	bool** GetTransposMatrix();

	const unsigned int GetMatrixSize();
	const unsigned int GetFigureID();	
	bool** GetMatrix();
	const Vector2D GetPos();

	void SetPos(const Vector2D&);
};