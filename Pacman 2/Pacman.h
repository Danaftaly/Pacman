#ifndef PACMAN_H
#define PACMAN_H

#include "Board.h"
#include "Creature.h"

class Pacman: public Creature {
	enum { Pac_Color = Color::BROWN, PAC_SIGN = '@' };

public:
	Pacman( bool _colorFlag ): Creature(PAC_SIGN, static_cast<Color>(Pac_Color), _colorFlag) {}
	void init(const Position& _initPos, Mode* _mode);
	void move(char& key, Board& board);
};

#endif