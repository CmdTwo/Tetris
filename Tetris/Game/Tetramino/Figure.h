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

	unsigned int _height;
	unsigned int _wight;

	Figure(Vector2D, unsigned int, bool);

private:
	Vector2D _pos;
	unsigned int _rotateMode;

	void Transposition();

	void Flip(bool);

	virtual void SetDefaultMatrix() = 0;

public:
	Figure();

	Figure(Vector2D);

	~Figure();

	//void Move();

	void Rotate();

	//unsigned int GetHeight;

	//unsigned int GetWight;

	const unsigned int GetMatrixSize();
	const unsigned int GetFigureID();	
	bool** GetMatrix();
	const Vector2D GetPos();

	void SetPos(const Vector2D&);

};