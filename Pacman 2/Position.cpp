#include "Position.h"

void Position::printToScreen(char ch)
{
	gotoxy(x, y);

	if (ch == GameSign_FOOD)
		ch = (char)PrintSign_FOOD;
	else if (ch == FileSign_BLANK)
		ch = (char)PrintSign_BLANK;

	cout << ch;
}