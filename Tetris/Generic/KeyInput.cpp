#include "KeyInput.h"

KeyInput::KeyInput()
{
}


KeyInput::~KeyInput()
{
}

KeyInput::Keys KeyInput::GetKeyInput()
{
	unsigned int first = _getch();
	unsigned int second = _getch();

	unsigned int result = first + second;

	switch (result)
	{
	case (299):
		return KeyInput::LeftRow;
	case (296):
		return KeyInput::UpRow;
	case(301):
		return KeyInput::RightRow;
	case(304):
		return KeyInput::DownRow;
	case(82):
	case(114):
	case(170):
	case(138):
		return KeyInput::R;
	case(27):
		return KeyInput::Esc;
	case(59):
		return KeyInput::F1;
	default:
		return KeyInput::NonGameKey;
	}
}
