#include "GameManager.h"

int main(int argc, char** argv)
{
	GameManager gameManager;

	clear_screen();

	try {
		gameManager.setGameMode(argc, argv);

		gameManager.run();
	}
	catch (const char* msg)
	{
		clear_screen();

		cout << msg << endl << endl;
	}

	return 0;
}