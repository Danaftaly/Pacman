#ifndef MODE_H
#define MODE_H

#include "Utils.h"
#include "Position.h"

enum class MODE {
	SIMPLE = 0,
	SAVE = 1,
	LOAD = 2,
	SILENT = 3
};

enum class FileFlag {
	QuitScreen = 'Q',
	Dead = 'D',
	InvalidScreen = 'X',
	Pacman = 'P',
	Ghost = 'G',
	Fruit = 'F',
	Appear = '+',
	Disappear = '-',
	Leave = 'L'
};

class Mode {
	enum { Left = 'a', Up = 'w', Right = 'd', Down = 'x', Stay = 's'};

	MODE gameMode;
	bool silent;
	fstream fSteps;
	fstream fResult;
	UINT gameCounter;
public:
	Mode(MODE _gameMode);
	void openFiles(string fileName);
	void closeFiles() { fSteps.close(); fResult.close(); }
	MODE getGameMode()const { return gameMode; }
	void saveStepToFile(const string str); 
	char getStepFromFile(); 
	void saveResultToFile(FileFlag flag);
	bool resultTest(FileFlag ch);
	void getFruitStats(Position& pos, char& sign);
	void saveFruitStats(Position& pos, char& sign);
	void initGameCounter() { gameCounter = 0; }
	void promoteGameCounter() { gameCounter++; }
	char peekStep();
	void moveStepCursur() { fSteps.get(); }
	void moveLineCurser() { string temp; std::getline(fSteps, temp); }
	bool isSilent()const { return silent; }
	~Mode();
};

#endif
