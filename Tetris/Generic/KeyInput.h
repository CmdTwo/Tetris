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
		F1,
		Esc
	};

	Keys GetKeyInput();

	KeyInput();
	~KeyInput();
};

