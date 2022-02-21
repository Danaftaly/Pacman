#ifndef GOOD_H
#define GOOD_H

#include "Best.h"
#include "Novice.h"

class Good : public Strategy {
	Strategy* strategy;
	int randRatio;
	int paceCounter;
public:
	Good(const int _randRatio) : randRatio(_randRatio), paceCounter(0), strategy(new Best) {}
	
	void botMove(const Board& board, Bot& bot, const Position pacPos) override;
	void setStrategy(Strategy* _strategy) { delete this->strategy; this->strategy = _strategy; }
	void initPacQurter() override { strategy->initPacQurter(); }

	~Good() { delete strategy; }
};

#endif