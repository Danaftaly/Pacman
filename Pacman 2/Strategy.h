#ifndef STRATEGY_H
#define STRATEGY_H

#include "Utils.h"
#include "Board.h"
#include "Bot.h"

class Strategy {
public:
	virtual void botMove(const Board& board, Bot& bot, const Position pacPos) = 0;
	virtual void initPacQurter(){}
	virtual bool isPathToPacExist(const Board& board, Bot& bot, const Position pacPos) { return true; }

	virtual ~Strategy() {}
};


#endif