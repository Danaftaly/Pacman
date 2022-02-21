#ifndef NOVICE_H
#define NOVICE_H

#include "Strategy.h"

class Novice : public Strategy {
	enum { Left = 'a', Up = 'w', Right = 'd', Down = 'x', Stay = 's', DEFAULT = 0 };
	char dirEncode[4] = { Left, Up, Right, Down };

	const int randRatio;
public:
	Novice(const int _randRatio) : randRatio(_randRatio) {}
	void botMove(const Board& board, Bot& bot, const Position pacPos = Position(-1, -1)) override;
};

#endif