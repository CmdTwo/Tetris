#pragma once
#include "../../Generic/Vector2D.h"
#include "../../Global/ConsoleManager.h"

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
	//unsigned int _figureID;
	unsigned int _rotateMode;
	unsigned int _height;
	unsigned int _wight;

	Figure(Vector2D, unsigned int, bool, ConsoleManager::ConsoleColor);

private:
	Vector2D _pos;
	
	ConsoleManager::ConsoleColor _color;

	void Transposition();

	void Transposition(bool** matrix, size_t size);

	void Flip(bool);

	virtual void SetDefaultMatrix() = 0;

	virtual void SetDefaultRotateMode();

public:

	Figure(Vector2D, ConsoleManager::ConsoleColor);

	~Figure();

	void Rotate(bool onPositive = true);

	void LocalMove(bool onVertical, bool onPositive);

	bool IsFreeSpaceArea(bool* begin, bool* end);

	void MoveOnX(unsigned int newX);
	void MoveOnY(unsigned int newY);

	bool* GetFreeSpaceIter(bool onVerical);

	bool** GetTransposMatrix();

	const unsigned int GetMatrixSize();

	//const unsigned int GetFigureID();	

	bool** GetMatrix();

	bool** GetCopyMatrix();

	const Vector2D GetPos();

	void SetPos(const Vector2D&);

	ConsoleManager::ConsoleColor GetColor();
};