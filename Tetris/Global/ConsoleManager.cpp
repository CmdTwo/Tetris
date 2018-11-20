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

void ConsoleManager::SetGameConsoleMode()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌쳌");
	//cfi.FontFamily = 3435973836;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
	//GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cfi);
}
