#include "ConsoleManager.h"



ConsoleManager::ConsoleManager()
{
	_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}


ConsoleManager::~ConsoleManager()
{
}

void ConsoleManager::SetCursosPosition(short x, short y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
