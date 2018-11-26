#pragma once
#include <conio.h>

class KeyInput
{
public:
	enum Keys
	{
		NonGameKey,
		LeftRow,
		UpRow,
		RightRow,
		DownRow,
		R,
		Enter,
	};

	Keys GetKeyInput();

	KeyInput();
	~KeyInput();
};

