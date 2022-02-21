#ifndef MENU_H
#define MENU_H

#include "Utils.h"
#include "Mode.h"

enum class CHOICE {
	START_GAME = '1',
	SPECIFIC_SCREEN = '2',
	INSTRUCTIONS = '8',
	EXIT = '9',
	COLORS = 'c'
};

class Menu
{
	CHOICE choice;
	const bool& colorFlag;

	void printPacHeader();
public:
	Menu(const bool& _colorFlag) : colorFlag(_colorFlag) {}
	void printWelcome();
	void printMenu(const Mode* mode);
	void printInstructions();
	
	void setChoice(CHOICE _choice) { choice = _choice; }
	CHOICE getChoice()const { return choice; }
};

#endif

