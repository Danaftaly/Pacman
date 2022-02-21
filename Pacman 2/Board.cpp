#include "Board.h"

void Board::fit1stLineForLegend()
{
	for (int ind = 0; ind < board[0].size(); ind++)
	{
		if (board[0][ind] == FileSign_LEGEND)
			if (board[0].size() - ind < LEGEND_WIDTH)
				board[0].resize(LEGEND_WIDTH - 1 + static_cast<int64_t>(ind));
	}
}

void Board::loadBoardFromFile(string fileName)
{
	board.clear();

	ifstream fBoard(fileName);

	if (!fBoard)
		throw "ERORR! Couldn't open the file!";

	string line;
	std::getline(fBoard, line);

	if (line.size() > MAX_WIDTH || line.size() == 0)
	{
		clear_screen();
		throw "Invalid board! Illegal first line";
	}

	board.push_back(line);

	fit1stLineForLegend();

	for (int i = 1; !fBoard.eof() && i < MAX_HEIGHT; i++)
	{
		std::getline(fBoard, line);

		while (line.size() < board[0].size())
			line.push_back(FileSign_FOOD);

		board.push_back(line.substr(0, board[0].size()));
	}

	fBoard.close();
}

int Board::Init(vector<Position>& startPositions, Mode* _mode)
{
	mode = _mode;

	int foodAmount = 0;
	bool isPacExist = false;
	bool isLegendExist = false;
	bool isValidBoard = true;

	startPositions.resize(2); // for Pacman's and legend's positions

	for (int row = 0; row < board.size(); row++)
	{
		for (int col = 0; col < board[row].size(); col++)
		{
			switch (board[row][col])
			{
			case PAC:
				if (isPacExist)
					throw "Invalid Board! Pacman exist more than once";

				startPositions[0] = Position(col, row);
				board[row][col] = GameSign_BLANK;
				isPacExist = true;
				break;
			case GHOST:
				if (startPositions.size() - 2 == MAX_GHOST_NUM)
					throw "Invalid Board! Too many ghosts";

				startPositions.push_back(Position(col, row));
				board[row][col] = GameSign_FOOD;
				foodAmount++;
				break;
			case FileSign_LEGEND :
				if (isLegendExist || static_cast<int64_t>(col) + LEGEND_WIDTH >= board[0].size() || static_cast<int64_t>(row) + LEGEND_HEIGHT >= MAX_HEIGHT)
					throw "Invalid Board! Illegal legend";

				for (int i = 0; i < LEGEND_HEIGHT; i++)
					for (int j = 0; j < LEGEND_WIDTH; j++) 
						board[static_cast<int64_t>(row) + i][static_cast<int64_t>(col) + j] = GameSign_WALL;

				startPositions[1] = Position(col, row);
				isLegendExist = true;
				break;
			case FileSign_FOOD:
				board[row][col] = GameSign_FOOD;
				foodAmount++;
				break;
			case FileSign_BLANK:
				break;
			case FileSign_WALL:
				break;
			default:
				if (!isalpha(board[row][col]))
					throw "Invalid Board! Unknown characters";

				break;
			}
		}
	}

	if (!isPacExist)
		throw "Invalid Board! Pacman is not exist";

	if (!isLegendExist)
	{
		if (board.size() + LEGEND_HEIGHT <= MAX_HEIGHT)
		{
			startPositions[1] = Position(0, board.size());
		}
		else if (board[0].size() + LEGEND_WIDTH <= MAX_WIDTH)
		{
			startPositions[1] = Position(board[0].size(), 0);
		}
		else
			throw "Invalid Board! Illegal legend";
	}

	return foodAmount;
}

void Board::print() 
{
	clear_screen();

	if (mode->isSilent())
		return;

	for (int row = 0; row < board.size(); row++) {
		for (int col = 0; col < board[0].size(); col++)
		{
			if (board[row][col] == GameSign_WALL)
			{
				if (this->colorFlag) setTextColor(Color::BLUE);
				cout << (char)PrintSign_WALL;
				if (this->colorFlag) setTextColor(Color::WHITE);
			}
			else if (board[row][col] == 'P')
			{
				if (this->colorFlag) setTextColor(Color::GREEN);
				cout << (char)PrintSign_PAC_LED;
				if (this->colorFlag) setTextColor(Color::WHITE);
			}
			else if (board[row][col] == 'A')
			{
				if (this->colorFlag) setTextColor(Color::BROWN);
				cout << (char)PrintSign_PAC_LED;
				if (this->colorFlag) setTextColor(Color::WHITE);
			}
			else if (board[row][col] == 'C')
			{
				if (this->colorFlag) setTextColor(Color::RED);
				cout << (char)PrintSign_PAC_LED;
				if (this->colorFlag) setTextColor(Color::WHITE);
			}
			else if (board[row][col] == GameSign_FOOD)
				cout << (char)PrintSign_FOOD;
			else if (board[row][col] == GameSign_BLANK || board[row][col] == FileSign_BLANK)
				cout << (char)PrintSign_BLANK;
			else if (isalpha(board[row][col]))
			{
				if (this->colorFlag) setTextColor(Color::BLUE);
				cout << (char)PrintSign_PAC_LED;
				if (this->colorFlag) setTextColor(Color::WHITE);
			}
		}
		cout << endl;
	}


}

int Board::getQurter(const int x, const int y)const
{
	if (isInRange(x, 0, (board[0].size() / 2)))
	{
		if (isInRange(y, 0, (board.size() / 2)))
			return 2;
		else
			return 3;
	}
	else
	{
		if (isInRange(y, 0, (board.size() / 2)))
			return 1;
		else
			return 4;
	}
}