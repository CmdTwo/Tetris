#pragma once
#include <Windows.h>

class ConsoleManager
{
private:
	HANDLE _handle;

	ConsoleManager();
	~ConsoleManager();



public:
	enum ConsoleColor :int {
		blue = 1,
		green = 2,
		lightBlue = 3,
		red = 4,
		violet = 5,
		orange = 6,
		defaultColor = 7
	};

	static void SetConoleColor(ConsoleColor color);
	
	static void ResetColors();

	static void SetCursosPosition(short x, short y);

	static void ClearConsole();
};

