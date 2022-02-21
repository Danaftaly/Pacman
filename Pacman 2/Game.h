#ifndef GAME_H
#define GAME_H

#include "Utils.h"
#include "Position.h"
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Strategy.h"
#include "Mode.h"

class Game {
	enum { ESC = 27, LeaveKey = 'l', DEFAULT = 0, INIT_LIVES = 3, FOOD = '.' };
	Color ghostColorEncode[4] = { Color::LIGHTRED, Color::LIGHTGREEN, Color::LIGHTCYAN, Color::LIGHTMAGENTA };
	enum { Legend_LU_Corner = 201, Legend_RU_Corner = 187, Legend_LD_Corner = 200, Legend_RD_Corner = 188, Legend_Horiz_Frame = 205, Legend_Vert_Frame = 186, Legend_Color = Color::LIGHTBLUE};
	enum { NOVICE = 0, GOOD = 1, BEST = 2 };
	enum { Lose = 0, Win = 1, Leave = 2 };

	string fileName;
	Board gameBoard;
	Position LegendPos;
	Mode* mode;

	Pacman pac; 
	vector<Ghost> ghosts;
	Fruit fruit;
	
	int lives;
	int score = 0;
	int foodAmount;
	bool colorFlag;
	int difficulty;
	int gameBeat = 1;

	void initGame();
	void printLegend();
	bool isGhostHit(const Position victim);
	bool ghostsMovement();
	bool PacFruitEatCheck();
	void fruitManager(bool& isPacAteFruit, const bool isPacDead);
	void pacEat();
	void pacDead();
	void gameBeatUpdate();
	void pause();
	bool leave();
public:
	Game(bool _colorFlag, int _difficulty, Mode* _mode);

	void loadNextScreen(string fileName);
	int run();
	
};
#endif
