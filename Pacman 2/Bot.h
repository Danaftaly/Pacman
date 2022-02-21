#ifndef BOT_H
#define BOT_H

#include "Creature.h"

class Strategy;

class Bot : public Creature {
	Strategy* strategy;
	int paceRatio;
public:
	Bot(char _sign, Color _color, bool _colorFlag, Position _initPos, int _paceRatio, Strategy* _strategy = nullptr) 
		: Creature(_sign, _color, _colorFlag, _initPos), paceRatio(_paceRatio), strategy(_strategy) {}

	bool isTimeToMove(const int gameBeat) { return (gameBeat % paceRatio == 0); }
	Strategy* getStrategy()const { return strategy; }
	void setStrategy(Strategy* _strategy) { delete this->strategy; this->strategy = _strategy; }
	int getPaceRatio()const { return paceRatio; }
	void setPaceRatio(const int _paceRatio) { paceRatio = _paceRatio; }
	
	~Bot() { delete this->strategy; }
};

#endif