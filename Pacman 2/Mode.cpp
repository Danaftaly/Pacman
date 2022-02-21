#include "Mode.h"

Mode::Mode(MODE _gameMode)
{
	if (_gameMode == MODE::SILENT)
	{
		silent = true;
		gameMode = MODE::LOAD;
	}
	else
	{
		silent = false;
		gameMode = _gameMode;
	}
}

void Mode::openFiles(string fileName)
{
	string baseFileName = fileName.substr(0, fileName.find_last_of('.'));

	if (gameMode == MODE::SAVE)
	{
		fSteps.open((baseFileName + ".steps"), std::ios::out);
		fResult.open((baseFileName + ".result"), std::ios::out);
		if (!fSteps.is_open() || !fResult.is_open())
			throw "ERORR! Files opening failure";
	}
	else if (gameMode == MODE::LOAD)
	{
		fSteps.open((baseFileName + ".steps"), std::ios::in);
		fResult.open((baseFileName + ".result"), std::ios::in);
		if (!fSteps.is_open() || !fResult.is_open())
			throw "Test failed!";
	}
}

void Mode::saveStepToFile(const string str)
{
	if (!fSteps.is_open())
		throw "ERORR! Files opening failure";

	fSteps << str << endl;
}

char Mode::getStepFromFile()
{
	string line;

	if (!fSteps.is_open())
		throw "Test failed!";

	std::getline(fSteps, line);

	if (fSteps.eof())
		throw "Test failed!";

	if (line[0] == Left || line[0] == Up || line[0] == Right || line[0] == Down || line[0] == Stay)
		return line[0];
	else
		throw "Test failed!";
}

void Mode::saveResultToFile(FileFlag flag)
{
	if (!fResult.is_open())
		throw "ERORR! Files opening failure";
	if (flag == FileFlag::InvalidScreen)
		fResult << (char)flag << endl;
	else
		fResult << (char)flag << gameCounter << endl;
}

bool Mode::resultTest(FileFlag flag)
{
	char fCh;
	UINT fGameCounter;

	if (!fResult.is_open())
		throw "Test failed";

	fResult >> fCh;

	if (fResult.eof())
		throw "Test failed";

	if (flag == FileFlag::InvalidScreen)
		return (fCh == (char)FileFlag::InvalidScreen);

	fResult >> fGameCounter;
	fResult.get();

	return ((char)flag == fCh && gameCounter == fGameCounter);
}

void Mode::getFruitStats(Position& pos, char& sign)
{
	string line;

	if (!fSteps.is_open())
		throw "Test failed!";

	std::getline(fSteps, line);

	if (fSteps.eof())
		throw "Test failed!";

	stringstream buffer(line);
	int x, y;

	buffer >> x;
	buffer >> y;
	buffer >> sign;

	pos.set(x, y);
}

void Mode::saveFruitStats(Position& pos, char& sign)
{
	if (!fSteps.is_open())
		throw "ERORR! Files opening failure";
	fSteps << string("") + (char)FileFlag::Fruit + (char)FileFlag::Appear << pos.get_x() << ' ' << pos.get_y() << ' ' << sign << endl;
}

char Mode::peekStep()
{
	if (!fSteps.is_open())
		throw "Test failed";

	char res = (char)fSteps.peek();

	if (res == (char)FileFlag::Appear)
		fSteps.get();
	if (res == (char)FileFlag::Disappear)
	{
		string temp;
		std::getline(fSteps, temp);
	}

	return res;
}

Mode::~Mode()
{
	if(fSteps.is_open())
		fSteps.close();

	if(fResult.is_open())
		fResult.close();
}
