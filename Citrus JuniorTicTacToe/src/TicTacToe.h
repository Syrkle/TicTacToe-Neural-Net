#pragma once

#include <vector>
#include <string>

class Game{
public:
	Game(int rowNum, int colNum);
	~Game();



	int input(float row, float col, int in);
	int getTurn();
	std::string printBoardState();
	std::vector<float> getRows();
	std::vector<float> getRand();

	std::vector<float> getNetBoard();
	std::vector<float> netInput(std::vector<float> in);

	std::vector<std::vector<float>> getWinningMoves();

	void clear();
	std::vector<std::vector<float>> getHistory();

	bool checkTie();
	bool checkP1Win();


private:
	std::vector<std::vector<float>> _rows;
	std::vector<std::vector<float>> _emptyRows;

	std::vector<std::vector<float>> _history;

	std::vector<std::vector<float>> _p1History;
	std::vector<std::vector<float>> _p2History;

	std::vector<std::vector<float>> _p1Moves;
	std::vector<std::vector<float>> _p2Moves;

	bool _p1Win;
	bool _tie;

	int _rowSize;
	int _colSize;
	int _diagSize;

	int _rowSlope;
	int _colSlope;

	int _turn;
	int _empty;
};
