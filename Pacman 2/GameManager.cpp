#include "GameManager.h"

GameManager::GameManager() : game(nullptr), mode(nullptr), menu(colorFlag)
{
	srand(time(NULL));

	for (const auto& file : fs::directory_iterator(fs::current_path()))
	{
		if(file.path().extension() == ".screen")
			fileNames.push_back(file.path().filename().string());
	}
}

void GameManager::run()
{
	if(!mode->isSilent())
		menu.printWelcome();

	hideCursor();

	bool exit = false;
	
	do {
		if (mode->getGameMode() != MODE::LOAD)
		{
			menu.printMenu(mode);

			menu.setChoice((CHOICE)tolower(_getch()));
		}
		else
			menu.setChoice(CHOICE::START_GAME);

		switch (menu.getChoice())
		{
		case CHOICE::SPECIFIC_SCREEN:
			if (mode->getGameMode() == MODE::SIMPLE)
				specificScreen();
			else
			{
				clear_screen();
				cout << "Invalid input! try again" << endl << endl;
				break;
			}
		
		case CHOICE::START_GAME:
			if (fileNames.empty() || (menu.getChoice() == CHOICE::SPECIFIC_SCREEN && filesQueue.empty()))
			{
				clear_screen();
				cout << "Error! There are no screens to load" << endl << endl;
				cout << "Press any key to go back to menu..." << endl;
				hideCursor();
				_getch();
				clear_screen();
				break;
			}
		
			startGame();
			break;
		case CHOICE::INSTRUCTIONS:
			menu.printInstructions();
			break;
		case CHOICE::EXIT:
			exit = true;
			clear_screen();
			break;
		case CHOICE::COLORS:
			colorFlag = !colorFlag;
			clear_screen();
			break;
		default:
			clear_screen();
			cout << "Invalid input! try again" << endl << endl;
			break;
		}
	} while (!exit);

	if(mode->getGameMode() != MODE::LOAD)
		cout << "Thanks for playing! See you next time!" << endl;
}

void GameManager::setGameMode(int argc, char** argv)
{
	MODE gameMode;
	string str;

	if (argc == 1)
	{
		gameMode = MODE::SIMPLE;
	}
	else
	{
		if (string("-save").compare(argv[1]) == 0)
		{
			if (argc > 2)
				throw "Invalid input!";

			gameMode = MODE::SAVE;
		}
		else if (string("-load").compare(argv[1]) == 0)
		{
			if (argc == 2)
				gameMode = MODE::LOAD;
			else if (argc == 3 && string("[-silent]").compare(argv[2]) == 0)
				gameMode = MODE::SILENT;
			else
				throw "Invalid input!";
		}
		else
			throw "Invalid input!";
	}

	mode = new Mode(gameMode);
}

void GameManager::startGame()
{
	int gameRes = Lose;
	int stage = 1;
	int difficulty = 0;

	if (mode->getGameMode() != MODE::LOAD)
		difficulty = setDifficulty();

	game = new Game(colorFlag, difficulty, mode);

	if (menu.getChoice() != CHOICE::SPECIFIC_SCREEN)
	{
		for (auto& currFile : fileNames)
			filesQueue.push(currFile);
	}

	stage = 1;

	while (!filesQueue.empty())
	{
		gameRes = Lose;

		string currFile = filesQueue.front();
		filesQueue.pop();

		try {
			game->loadNextScreen(currFile);

			gameRes = game->run();
			clear_screen();

			if (gameRes != Win)
			{
				while (!filesQueue.empty())
					filesQueue.pop();

				if(gameRes == Lose)
					if (mode->getGameMode() != MODE::LOAD)
						cout << "Game over! Have another try.." << endl << endl;
			}
			else if (!filesQueue.empty())
			{
				if (mode->getGameMode() != MODE::LOAD)
				{
					cout << "Nicely done! you completed stage " << stage << " !!" << endl;
					cout << endl << "Press any key to load the next screen..." << endl;
					hideCursor();
					_getch();

				}
				else if (!mode->isSilent())
				{
					for (int i = 3; i > 0; i--)
					{
						cout << "Test of stage " << stage << " succeeded" << endl << endl;
						cout << "Next test will begin in " << i << ".." << endl;
						hideCursor();
						Sleep(1000);
						clear_screen();
					}
				}

				stage++;
			}
		}
		catch (const char* msg) {
			exceptionsHandler(msg);
		}

		if (mode->getGameMode() != MODE::SIMPLE)
			mode->closeFiles();
	}

	if (mode->getGameMode() != MODE::LOAD)
	{
		if (gameRes == Win)
			cout << "You win!!! You are a Pacman master!" << endl << endl;

		if (gameRes != Leave)
		{
			cout << "Press any key to go back to menu..." << endl;
			hideCursor();
			_getch();
			clear_screen();
		}
	}
	else
	{
		throw "Test ended successfuly!";
	}

	delete game;
	game = nullptr;
}

void GameManager::specificScreen()
{
	clear_screen();
	string fileName;

	cout << "Please enter a file name with extention \".screen\" :" << endl;
	cin >> fileName;

	for (const auto& curr : fileNames)
	{
		if (curr == fileName)
		{
			filesQueue.push(curr);
			return;
		}
	}
}

int GameManager::setDifficulty()
{
	clear_screen();

	bool isValidChoice = false;
	char choice;
	int res;

	while (!isValidChoice)
	{
		cout << "Choose game difficulty:" << endl << endl;
		cout << "(a) Best" << endl;
		cout << "(b) Good" << endl;
		cout << "(c) Novice" << endl;

		hideCursor();

		choice = tolower(_getch());

		switch (choice)
		{
		case Best:
			res = BEST;
			isValidChoice = true;
			break;
		case Good:
			res = GOOD;
			isValidChoice = true;
			break;
		case Novice:
			res = NOVICE;
			isValidChoice = true;
			break;
		default:
			clear_screen();
			cout << "Invalid input!" << endl << endl;
			break;
		}
	}

	return res;
}

void GameManager::exceptionsHandler(const char* msg)
{
	if (strcmp(msg, "Test failed!") == 0)
		throw "Test failed!";

	if (strcmp(msg, "ERORR! Files opening failure") == 0)
		throw "ERORR! Files opening failure";

	if (mode->getGameMode() != MODE::LOAD)
	{
		if (mode->getGameMode() == MODE::SAVE)
			mode->saveResultToFile(FileFlag::InvalidScreen);

		cout << msg << endl;

		if (filesQueue.empty())
			cout << endl << "There are no more screens to load," << endl;
		else
		{
			cout << endl << "Press any key to load the next screen..." << endl;
			_getch();
		}
	}
	else
	{
		if (!mode->resultTest(FileFlag::InvalidScreen))
			throw "Test failed!";

		if (!mode->isSilent())
		{
			cout << msg << endl;
			Sleep(3000);
			clear_screen();

			if (!filesQueue.empty())
			{
				for (int i = 3; i > 0; i--)
				{
					cout << "Loading next screen to test in " << i << ".." << endl;
					hideCursor();
					Sleep(1000);
					clear_screen();
				}
			}
		}
	}
}

GameManager::~GameManager()
{
	delete game;
	delete mode;
}