#ifndef GHOST_H
#define GHOST_H

#include "Bot.h"
#include "Best.h"
#include "Good.h"
#include "Novice.h"

class Strategy;

class Ghost : public Bot{
	enum { WALL = '#', GHOST_SIGN = 234, PACE_RATIO = 2, RAND_RATIO = 5};
	enum { NOVICE = 0, GOOD = 1, BEST = 2};

public:
	Ghost(Color _color, bool _colorFlag, Position _initPos, Strategy* _strategy = nullptr) : Bot(static_cast<char>(GHOST_SIGN), _color, _colorFlag, _initPos, PACE_RATIO, _strategy){}

	void init(int difficulty, Mode* _mode, const Board& board, const Position pacPos);
	void initPacQurter();
	void move(const Board& board, const Position pacPos);
};

#endif