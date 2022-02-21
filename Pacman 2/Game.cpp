#include "Game.h"

Game::Game(bool _colorFlag, int _difficulty, Mode* _mode) : colorFlag(_colorFlag), pac(_colorFlag), gameBoard(_colorFlag), fruit(_colorFlag), difficulty(_difficulty), mode(_mode) {}

void Game::loadNextScreen(string fileName)
{
	if(mode->getGameMode() != MODE::SIMPLE)
		mode->openFiles(fileName);

	gameBoard.loadBoardFromFile(fileName);
	
	initGame();
}

void Game::initGame()
{
	clear_screen();

	gameBeat = 1;
	lives = INIT_LIVES;

	if(mode->getGameMode() != MODE::SIMPLE)
		mode->initGameCounter();

	vector<Position> startPositions;
	foodAmount = gameBoard.Init(startPositions, mode);
	
	gameBoard.print();

	pac.init(startPositions[0], mode);

	LegendPos = startPositions[1];
	printLegend();

	ghosts.clear();
	ghosts.reserve(startPositions.size() - 2);

	for (int i = 0; i < startPositions.size() - 2; i++)
	{
		ghosts.push_back(Ghost(ghostColorEncode[i], colorFlag, startPositions[static_cast<int64_t>(i) + 2]));
		
		ghosts[i].init(difficulty, mode, gameBoard, pac.getPos());
	}

	fruit.setMode(mode);
	fruit.setSign(DEFAULT);
}

void Game::printLegend()
{
	if (mode->isSilent())
		return;

	if (colorFlag) setTextColor((Color)Legend_Color);
	gotoxy(LegendPos.get_x(), LegendPos.get_y());
	cout << (char)Legend_LU_Corner;

	for (int i = 0; i < 18; i++)
		cout << (char)Legend_Horiz_Frame;

	cout << (char)Legend_RU_Corner;

	gotoxy(LegendPos.get_x(), LegendPos.get_y() + 1);
	cout << (char)Legend_Vert_Frame;

	if (colorFlag) setTextColor(Color::WHITE);
	cout << "HP:" << lives << " Score:";
	cout << std::setw(7) << score;

	if (colorFlag) setTextColor(Color::LIGHTBLUE);
	cout << (char)Legend_Vert_Frame;

	gotoxy(LegendPos.get_x(), LegendPos.get_y() + 2);
	cout << (char)Legend_LD_Corner;

	for (int i = 0; i < 18; i++)
		cout << (char)Legend_Horiz_Frame;

	cout << (char)Legend_RD_Corner;

	if (colorFlag) setTextColor(Color::WHITE);
}

int Game::run()
{
	char key = DEFAULT;
	bool isPacDead = false;
	bool isPacAteFruit = false;

	while (lives > 0 && foodAmount > 0)
	{
		hideCursor();

		if (mode->getGameMode() == MODE::LOAD)
		{
			if (mode->peekStep() == (char)FileFlag::Pacman)
			{
				mode->moveStepCursur();
				key = mode->getStepFromFile();
			}
			else if (mode->peekStep() == (char)FileFlag::Leave)
				break;
			else
				throw "Test failed!";
				
		}
		else
		{
			if (_kbhit())
			{
				key = tolower(_getch());

				if (key == ESC)
					pause();
				else if (key == LeaveKey && leave())
				{
					if (mode->getGameMode() == MODE::SAVE)
						mode->saveStepToFile(string("") + (char)FileFlag::Leave);

					break;
				}
			}
		}
		pac.move(key, gameBoard);

		isPacDead = isGhostHit(pac.getPos());
		isPacAteFruit = PacFruitEatCheck();

		if (pac.getDirection() != DEFAULT && !isPacDead)
		{		
			isPacDead = ghostsMovement();
		}
		
		fruitManager(isPacAteFruit, isPacDead);
		
		if (isPacDead)
		{
			pacDead();
			isPacDead = false;
			key = DEFAULT;
		}
		
		pacEat();

		if (mode->getGameMode() != MODE::LOAD)
			Sleep(200);
		else if (!mode->isSilent())
			Sleep(50);
		
		if (pac.getDirection() != DEFAULT)
		{
			gameBeatUpdate();

			if (mode->getGameMode() != MODE::SIMPLE)
				mode->promoteGameCounter();
		}
	}

	if (mode->getGameMode() == MODE::SAVE)
		mode->saveResultToFile(FileFlag::QuitScreen);

	if (mode->getGameMode() == MODE::LOAD)
		if (!mode->resultTest(FileFlag::QuitScreen))
			throw "Test failed!";

	if (lives == 0)
		return Lose;
	else if (foodAmount == 0)
		return Win;
	else
		return Leave;
}

bool Game::PacFruitEatCheck()
{
	return (pac.getPos() == fruit.getPos());
}

void Game::fruitManager(bool& isPacAteFruit, const bool isPacDead)
{
	if (mode->getGameMode() == MODE::LOAD)
	{
		if (mode->peekStep() == (char)FileFlag::Fruit)
			mode->moveStepCursur();
		else
			return;
	}


	if (!fruit.isExist())
	{
		if (fruit.isTimeToAppear(pac.getPaceCounter()) && !isPacDead)
		{
			fruit.init(gameBoard, pac.getPos());
			pac.setPaceCounter(0);
		}
	}
	else  // fruit is exist
	{
		if (mode->getGameMode() == MODE::LOAD)
		{
			if (isalpha(mode->peekStep()))
			{
				fruit.move(gameBoard);

				if (PacFruitEatCheck())
				{
					isPacAteFruit = true;
					
					mode->moveLineCurser();
				}
			}
			else
			{
				if (!isPacAteFruit)
				{
					fruit.remove(gameBoard.getChar(fruit.getPos()));
					pac.setPaceCounter(0);
				}
			}
		}
		else
		{
			if (!isPacAteFruit)
			{
				if (fruit.isTimeToDisappear(pac.getPaceCounter()) || isGhostHit(fruit.getPos()) || isPacDead)
				{
					fruit.remove(gameBoard.getChar(fruit.getPos()));
					pac.setPaceCounter(0);
				}
				else if (fruit.isTimeToMove(gameBeat))
				{
					fruit.move(gameBoard);

					if (PacFruitEatCheck())
						isPacAteFruit = true;
				}
					
			}
		}

		if (isPacAteFruit)
		{
			score += (fruit.getSign() - '0');
			printLegend();

			fruit.remove(gameBoard.getChar(fruit.getPos()));

			if (!isPacDead)
				pac.draw();

			pac.setPaceCounter(0);

			isPacAteFruit = false;
		}
	}
}

bool Game::isGhostHit(const Position victimPos)
{
	for (auto& i : ghosts)
		if (i.getPos() == victimPos)
			return true;

	return false;
}

bool Game::ghostsMovement()
{
		for (auto& ghost : ghosts)
		{
			if (ghost.isTimeToMove(gameBeat))
				ghost.move(gameBoard, pac.getPos());
		}

		for (auto& ghost : ghosts)
		{
			if (ghost.isTimeToMove(gameBeat))
				ghost.draw();
		}

		return isGhostHit(pac.getPos());
}

void Game::pacEat()
{
	Position pacPos = pac.getPos();

	if (gameBoard.getChar(pacPos) == FOOD)
	{
		foodAmount--;
		score++;

		printLegend();

		gameBoard.removeFood(pacPos);
	}
}

void Game::pacDead()
{
	lives--;

	if (mode->getGameMode() == MODE::SAVE)
		mode->saveResultToFile(FileFlag::Dead);

	if (mode->getGameMode() == MODE::LOAD)
		if (!mode->resultTest(FileFlag::Dead))
			throw "Test failed!";

	printLegend();

	if (lives == 0)
		return;

	if(!mode->isSilent())
		pac.getPos().printToScreen(gameBoard.getChar(pac.getPos()));

	pac.setToStartPos();
	pac.setPaceCounter(0);
	
	for (auto& ghost : ghosts)
	{
		if (!mode->isSilent())
			ghost.getPos().printToScreen(gameBoard.getChar(ghost.getPos()));

		ghost.setToStartPos();
		ghost.initPacQurter();
	}
}

void Game::gameBeatUpdate()
{
	if (gameBeat == fruit.getPaceRatio())
		gameBeat = 1;
	else
		gameBeat++;
}

void Game::pause()
{
	if(colorFlag) setTextColor(Color::LIGHTRED);

	gotoxy(LegendPos.get_x(), LegendPos.get_y());
	cout << "   Game paused...   ";

	gotoxy(LegendPos.get_x(), LegendPos.get_y() + 1);
	cout << "                    ";

	gotoxy(LegendPos.get_x(), LegendPos.get_y() + 2);
	cout << "Press ESC to resume ";

	if (colorFlag) setTextColor(Color::WHITE);

	while (_getch() != ESC);

	printLegend();
}

bool Game::leave()
{
	if (colorFlag) setTextColor(Color::LIGHTRED);

	gotoxy(LegendPos.get_x(), LegendPos.get_y());
	
	cout << "Leaving already? :( ";

	gotoxy(LegendPos.get_x(), LegendPos.get_y() + 1);
	cout << "                    ";

	gotoxy(LegendPos.get_x(), LegendPos.get_y() + 2);
	cout << "    Press  Y / N    ";
	
	if (colorFlag) setTextColor(Color::WHITE);

	char choice;

	do
	{
		choice = tolower(_getch());
	} while (choice != 'y' && choice != 'n');

	if (choice == 'y')
		return true;
	else
	{
		printLegend();

		return false;
	}
}
