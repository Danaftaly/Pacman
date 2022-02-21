#ifndef FRUIT_H
#define FRUIT_H

#include "Bot.h"
#include "Novice.h"

class Fruit : public Bot
{
	enum { Fruit_Color = Color::PURPLE_CYAN, RAND_RATIO = 5, PACE_RATIO = 8};
	enum { FileSign_BLANK = '%' };
	
	bool updateAppearance;
protected:
	int whenToDisappear;
	int whenToAppear;
public:
	Fruit(bool _colorFlag) : Bot(DEFAULT, static_cast<Color>(Fruit_Color), _colorFlag, Position(-1, -1), PACE_RATIO, new Novice(RAND_RATIO)) { whenToAppear = myRand(15, 35); }

	void init(const Board& board, const Position& pacPos);
	void remove(const char ch);
	void move(Board& board);
	bool isLlegalPos(const Position& pos, const Position& pacPos, const Board& board);
	bool isExist() { return this->getSign() != DEFAULT; }
	
	bool isTimeToAppear(const int pacPaceCounter);
	bool isTimeToDisappear(const int pacPaceCounter);
};




#endif
