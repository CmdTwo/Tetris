#pragma once
#include <Windows.h>

class ConsoleManager
{
private:
	HANDLE _handle;

	ConsoleManager();
	~ConsoleManager();

public:
	static void SetCursosPosition(short, short);
};

