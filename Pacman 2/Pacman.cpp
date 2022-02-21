#include "Pacman.h"

void Pacman::init(const Position& _initPos, Mode* _mode)
{
	setMode(_mode);
	setInitPos(_initPos);
	setToStartPos();
	setPaceCounter(0);
}

void Pacman::move(char& key, Board& board)
{
	if (key != Left && key != Up && key != Right && key != Down && key != Stay)
	{
		if (this->getDirection() == DEFAULT)
			return;
	}
	else
		this->setDirection(key);

	Position tempPos = this->getPos();

	generateNewPos(tempPos, this->getDirection(), board);

	if (this->getDirection() != Stay && !board.isBlocked(tempPos))
	{
		Creature::move(tempPos, BLANK);

		this->setPaceCounter(getPaceCounter() + 1);
	}

	if(mode->getGameMode() == MODE::SAVE)
		mode->saveStepToFile(string("") + (char)FileFlag::Pacman + this->getDirection());
}

