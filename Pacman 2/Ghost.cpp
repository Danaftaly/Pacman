#include "Ghost.h"

void Ghost::init(int difficulty, Mode* _mode, const Board& board, const Position pacPos)
{
	setMode(_mode);

	switch (difficulty)
	{
	case NOVICE:
		setStrategy(new Novice(RAND_RATIO));
		break;
	case GOOD:
		setStrategy(new Good(RAND_RATIO));
		break;
	case BEST:
		setStrategy(new Best);
		break;
	}

	this->setToStartPos();

	this->initPacQurter();

	setPaceCounter(0);

	if (difficulty == GOOD || difficulty == BEST)
		if (!this->getStrategy()->isPathToPacExist(board, *this, pacPos))
			this->setStrategy(new Novice(RAND_RATIO));
}

void Ghost::move(const Board& board, const Position pacPos)
{
	if (mode->getGameMode() == MODE::LOAD)
	{
		if (mode->peekStep() == (char)FileFlag::Ghost)
		{
			mode->moveStepCursur();

			Position newPos;

			char newDirection = getMode()->getStepFromFile();
			setDirection(newDirection);
			generateNewPos(newPos, newDirection, board);
			Creature::move(newPos, board.getChar(getPos()));
		}
		else
			throw "Test failed!";
	}
	else
	{
		this->getStrategy()->botMove(board, *this, pacPos);

		if (this->mode->getGameMode() == MODE::SAVE)
			mode->saveStepToFile(string("") + (char)FileFlag::Ghost + this->getDirection());
	}
}

void Ghost::initPacQurter()
{
	this->getStrategy()->initPacQurter();
}


