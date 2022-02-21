#include "Fruit.h"

void Fruit::init(const Board &board, const Position& pacPos)
{	
	Position pos;
	char sign;

	if (mode->getGameMode() == MODE::LOAD)
	{
		mode->getFruitStats(pos, sign);
	}
	else
	{
		do
		{
			pos.set(myRand(0, board.getWidth()), myRand(0, board.getHeight()));
		} while ((!isLlegalPos(pos, pacPos, board)));

		sign = '0' + myRand(5, 9);
		whenToDisappear = myRand(25, 40);

		if (mode->getGameMode() == MODE::SAVE)
			mode->saveFruitStats(pos, sign);
	}
	
	setInitPos(pos);
	setSign(sign);

	this->draw();

	setPaceCounter(0);
}

void Fruit::remove(const char ch)
{
	if (!mode->isSilent())
		this->getPos().printToScreen(ch);

	setSign(DEFAULT);
	whenToAppear = myRand(15, 40);
	this->setInitPos(Position(-1, -1));

	if (mode->getGameMode() == MODE::SAVE)
		mode->saveStepToFile(string("") + (char)FileFlag::Fruit + (char)FileFlag::Disappear);
}

bool Fruit::isLlegalPos(const Position& pos, const Position& pacPos, const Board& board)
{
	return (!(pos == pacPos) && !board.isBlocked(pos) && board.getChar(pos) != FileSign_BLANK);
}

bool Fruit::isTimeToAppear(const int pacPaceCounter)
{
	return ((mode->getGameMode() == MODE::LOAD && mode->peekStep() == (char)FileFlag::Appear || whenToAppear == pacPaceCounter));
}

bool Fruit::isTimeToDisappear(const int pacPaceCounter)
{
		return whenToDisappear == pacPaceCounter;
}

void Fruit::move(Board& board)
{
	if (mode->getGameMode() == MODE::LOAD)
	{
		Position newPos;

		char newDirection = getMode()->getStepFromFile();
		setDirection(newDirection);
		generateNewPos(newPos, newDirection, board);
		Creature::move(newPos, board.getChar(getPos()));
	}
	else
	{
		this->getStrategy()->botMove(board, *this, Position(-1, -1));

		if (mode->getGameMode() == MODE::SAVE)
			mode->saveStepToFile(string("") + (char)FileFlag::Fruit + this->getDirection());
	}
}
