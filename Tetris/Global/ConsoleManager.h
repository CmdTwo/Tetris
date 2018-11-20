#pragma once
#include <Windows.h>

class ConsoleManager
{
private:
	HANDLE _handle;

	ConsoleManager();
	~ConsoleManager();

public:
	static void SetGameConsoleMode();
	static void SetCursosPosition(short x, short y);
};

