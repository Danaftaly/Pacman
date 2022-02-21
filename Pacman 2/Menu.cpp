#include "Menu.h"

void Menu::printWelcome()
{
	fstream fWelcome("Pacmacn_welcome.txt", std::ios::in);

	if(!fWelcome.is_open())
		throw "ERORR! Files opening failure";

	string line;

	while (std::getline(fWelcome, line))
	{
		cout << line << endl;
	}

	hideCursor();

	Sleep(3000);

	clear_screen();

	fWelcome.close();
}

void Menu::printMenu(const Mode* mode) {

	printPacHeader();

	cout << "(1) Start a new game" << endl;

	if(mode->getGameMode() == MODE::SIMPLE)
		cout << "(2) Play a specific screen" << endl;

	cout << "(8) Present instructions and controls" << endl;
	cout << "(9) EXIT" << endl << endl << endl << endl;
	cout << "(c) Do you want to play with colors? : ";
	cout << (colorFlag ? "Yes" : "No") << endl;

	hideCursor();
}

void Menu::printInstructions()
{
	clear_screen();

	printPacHeader();

	cout << "Goal:" << endl;
	cout << "Guide Pacman around the maze and eat all the little white dots while" << endl;
	cout << "avoiding those nasty ghosts." << endl << endl;
	cout << "Try catch and eat those fruits and gain some extra points" << endl << endl;
	cout << "Controls:" << endl;
	cout << "A : Left\tESC : Pause" << endl << "W : Up  \tL   : Leave to menu" << endl;
	cout << "D : Right" << endl << "X : Down" << endl << "S : Stay" << endl << endl;
	cout << "Press any key to get back to the menu.." << endl;

	hideCursor();
	char ch = _getch();
	clear_screen();
}

void Menu::printPacHeader()
{
	cout << " _ __   __ _  ___ _ __ ___   __ _ _ __" << endl;
	cout << "| '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ " << endl;
	cout << "| |_) | (_| | (__| | | | | | (_| | | | |" << endl;
	cout << "| .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|" << endl;
	cout << "| |" << endl;
	cout << "|_|" << endl << endl;
}
