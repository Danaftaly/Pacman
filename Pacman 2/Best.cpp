#include "Best.h"

void Best::botMove(const Board& board, Bot& bot, const Position pacPos)
{
	int currPacQurter = board.getQurter(pacPos);

	if (pacQurter != currPacQurter || pacQurter == board.getQurter(bot.getPos()) || pathToPac.empty())
	{
		while (!pathToPac.empty())
			pathToPac.pop();

		pathToPac = aStarAlgorithm(board, bot.getPos(), pacPos);

		pacQurter = currPacQurter;
	}
	
    Position tempPos;

        tempPos = pathToPac.top();
        pathToPac.pop();

        bot.setDiretcion(tempPos);
        bot.move(tempPos, board.getChar(bot.getPos()));
}

bool Best::isPathToPacExist(const Board& board, Bot& bot, const Position pacPos)
{
    stack<Position> resStack;

    resStack = aStarAlgorithm(board, bot.getPos(), pacPos);

    return !resStack.empty();
}

stack<Position> Best::aStarAlgorithm(const Board& board, const Position pos, const Position pacPos)
{
    stack<Position> resStack;

    vector<vector<bool>> closedList;
    closedList.resize(board.getHeight());

    vector<vector<cell>> cellDetails;
    cellDetails.resize(board.getHeight());

    for (int row = 0; row < board.getHeight(); row++)
    {
        closedList[row].resize(board.getWidth(), false);
        cellDetails[row].resize(board.getWidth());
    }

    int curr_x, curr_y;
 
    curr_x = pos.get_x(), curr_y = pos.get_y();
    cellDetails[curr_y][curr_x].f = 0;
    cellDetails[curr_y][curr_x].g = 0;
    cellDetails[curr_y][curr_x].h = 0;
    cellDetails[curr_y][curr_x].parent = { curr_y, curr_x };

    std::priority_queue<Tuple, std::vector<Tuple>, std::greater<Tuple>> openList;

    openList.emplace(0, curr_y, curr_x);

    int dx[4] = {0, -1, 0, 1};  // up - left - down - right
    int dy[4] = {-1, 0, 1, 0};

    while (!openList.empty())
    {
        const Tuple& p = openList.top();
        curr_y = std::get<1>(p); // second element of tupla
        curr_x = std::get<2>(p); // third element of tupla

        openList.pop();
        closedList[curr_y][curr_x] = true;

        for (int i = 0; i < 4; i++)
        {
            Pair neighbour(curr_y + dy[i], curr_x + dx[i]);

            if (board.isValidPos(neighbour.second, neighbour.first))
            {
                if (pacPos.get_x() == neighbour.second && pacPos.get_y() == neighbour.first)
                {
                    cellDetails[neighbour.first][neighbour.second].parent = { curr_y, curr_x };
                    return tracePath(cellDetails, pacPos);
                }
                else if (!closedList[neighbour.first][neighbour.second] && !board.isBlocked(neighbour.second, neighbour.first))
                {
                    int gNew = cellDetails[curr_y][curr_x].g + 1;
                    int hNew = calculateHValue(neighbour, pacPos);
                    int fNew = gNew + hNew;

                    if (cellDetails[neighbour.first][neighbour.second].f == -1 || cellDetails[neighbour.first][neighbour.second].f > fNew)
                    {
                        openList.emplace(fNew, neighbour.first, neighbour.second);

                        cellDetails[neighbour.first][neighbour.second].g = gNew;
                        cellDetails[neighbour.first][neighbour.second].h = hNew;
                        cellDetails[neighbour.first][neighbour.second].f = fNew;
                        cellDetails[neighbour.first][neighbour.second].parent = { curr_y, curr_x };
                    }
                }
            }
        }
    }

    return resStack;
}

stack<Position> Best::tracePath(const vector<vector<cell>>& cellDetails, const Position pacPos)
{
    stack<Position> Path;

    int row = pacPos.get_y();
    int col = pacPos.get_x();

    Path.push(Position(col, row));

    Pair next_node = cellDetails[row][col].parent;
    row = next_node.first;
    col = next_node.second;

    while (cellDetails[row][col].parent != next_node)
    {
        Path.push(Position(next_node.second, next_node.first));
        next_node = cellDetails[row][col].parent;
        row = next_node.first;
        col = next_node.second;
    } 

    return Path;
}
