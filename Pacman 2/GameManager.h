#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Utils.h"
#include "Game.h"
#include "Menu.h"

namespace fs = std::filesystem;

class GameManager {
	enum { LOSE = 0};
	enum { NOVICE = 0, GOOD = 1, BEST = 2 };
	enum { Best = 'a', Good = 'b', Novice = 'c' };
	enum { Lose = 0, Win = 1, Leave = 2 };

	Game* game;
	Mode* mode;
	Menu menu;
    vector<string> fileNames;
	queue<string> filesQueue;
	bool colorFlag = true;

	void startGame();
	void specificScreen();
	int setDifficulty();
	void exceptionsHandler(const char* msg);
public:
	GameManager();

	void run();
	void setGameMode(int argc, char** argv);
	
	~GameManager();
};

#endif
