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

	unsigned int _height;
	unsigned int _wight;

	Figure(unsigned int, bool);

private:
	Vector2D _pos;
	unsigned int _rotateMode;

	void Transposition();

	void Flip(bool);

	virtual void SetDefaultMatrix() = 0;

public:	
	Figure();

	~Figure();

	//void Move();

	void Show();

	void Rotate();

	unsigned int GetHeight;

	unsigned int GetWight;
};

