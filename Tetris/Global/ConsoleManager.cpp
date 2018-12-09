#include "ConsoleManager.h"
#include <cwchar>

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

void ConsoleManager::SetConoleColor(ConsoleColor color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ConsoleManager::ResetColors()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
}

void ConsoleManager::ClearConsole()
{
	system("cls");
}