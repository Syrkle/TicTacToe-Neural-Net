#include "TicTacToe.h"

#include <algorithm>
#include <numeric>
#include <cmath>
#include <sstream>
#include <iostream>


Game::Game(int rowNum, int colNum){
	std::vector<std::vector<float>> _p1Moves;
	std::vector<std::vector<float>> _p2Moves;

	_p1Win = true;
	_turn = 0;
	_rowSize = rowNum;
	_colSize = colNum;
	_empty = -1 * (rowNum * colNum);
	_tie = false;

	if((rowNum > 10000 || colNum > 10000 ) && (rowNum > 1000 || colNum > 1000)){
		rowNum = std::log(rowNum) * 1000;
		colNum = std::log(colNum) * 1000;
	}
	int gcdnum = std::__gcd(rowNum, colNum);

	_rowSlope = rowNum / gcdnum;
	_colSlope = colNum / gcdnum;

	if(rowNum == colNum){
		_diagSize = rowNum;
	}
	else{
		_diagSize = std::sqrt((rowNum * rowNum) + (colNum * colNum));
	}

	std::vector<float> temp;
	for(int i = 0; i < rowNum; i++){
		for(int k = 0; k < colNum; k++){
			temp.push_back(_empty);
		}
		_emptyRows.push_back(temp);
		temp.clear();
	}
	_rows = _emptyRows;

};

Game::~Game(){};


std::vector<float> Game::getNetBoard(){
	std::vector<float> netIN;

	return netIN;
}

std::vector<float> Game::netInput(std::vector<float> in){
	std::vector<float> temp;

	int cur = 0;
	int pos = 0;

	for(int i = 0; i < in.size(); i++){
		if(in.at(i) > cur){
			cur = in.at(i);
			pos = i;
		}
	}

	switch(pos){
		case 0:
			temp = {0, 0};
			break;
		case 1:
			temp = {0, 1};
			break;
		case 2:
			temp = {0, 2};
			break;
		case 3:
			temp = {1, 0};
			break;
		case 4:
			temp = {1, 1};
			break;
		case 5:
			temp = {1, 2};
			break;
		case 6:
			temp = {2, 0};
			break;
		case 7:
			temp = {2, 1};
			break;
		case 8:
			temp = {2, 2};
			break;
	}

	int col;
	int row;
	int loc = _rows[temp.at(0)].at(temp.at(1));

	if(loc > _empty){
		for(int i = 0; i < _rowSize; i++){
			for(int k = 0; k < _colSize; k++){
				loc = _rows[i].at(k);
				if(loc == _empty){
					col = k;
					row = i;
					temp = {row, col};

					return temp;
				}

			}
		}
	}


	return temp;
}





/*
std::vector<float> Game::netInput(std::vector<float> in){
	int row = in.at(0) + in.at(1);
	int col = in.at(2) + in.at(3);

	//decodes column from net
	if(in.at(0) >= 0.5){
		if(in.at(1) >= 0.5){
			row = 2;
		}
		else{
			row = 1;
		}
	}
	else{
		row = 0;
	}
	//decodes column from net
	if(in.at(2) >= 0.5){
		if(in.at(3) >= 0.5){
			col = 2;
		}
		else{
			col = 1;
		}
	}
	else{
		col = 0;
	}

	std::vector<float> loc;
	int temp = _rows[row].at(col);

	if(temp > _empty){
		for(int i = 0; i < _rowSize; i++){
			for(int k = 0; k < _colSize; k++){
				temp = _rows[i].at(k);
				if(temp == _empty){
					col = k;
					row = i;
					loc.push_back(row);
					loc.push_back(col);

					return loc;
				}
			}
		}
	}
	else{
		loc.push_back(row);
		loc.push_back(col);
	}

	return loc;
}
*/


std::vector<float> Game::getRows(){
	std::vector<float> rows;
	std::vector<float> p1;
	std::vector<float> p2;

	for(int i = 0; i < _rows.size(); i++){
		for(int k = 0; k < _rows[i].size(); k++){
			if(_rows[i].at(k) == 2.0){
				p1.push_back(1);
				p2.push_back(0);
			}
			else if(_rows[i].at(k) == 1.0){
				p1.push_back(0);
				p2.push_back(1);
			}
			else{
				p1.push_back(0);
				p2.push_back(0);
			}
		}
	}
	/*
	for(int i = 0; i < this->_rowSize; i++){
		//rows.insert(std::end(rows), std::begin(this->_rows.at(i)), std::end(this->_rows.at(i)));
		rows.insert(std::end(rows), std::begin(p1), std::end(p1));
		rows.insert(std::end(rows), std::begin(p2), std::end(p2));
	}
	*/

	rows.insert(std::end(rows), std::begin(p1), std::end(p1));
	rows.insert(std::end(rows), std::begin(p2), std::end(p2));

	return rows;
}


std::vector<float> Game::getRand(){
	std::vector<float> loc;
	int row = (std::rand() % 3);
	int col = (std::rand() % 3);
	int temp = _rows[row].at(col);
	bool running = true;

	while(running){
		if(temp > _empty){
			row = (std::rand() % 3);
			col = (std::rand() % 3);
			temp = _rows[row].at(col);
		}
		else{
			running = false;
		}
	}

	/*
	if(temp > _empty){
		for(int i = 0; i < _rowSize; i++){
			for(int k = 0; k < _colSize; k++){
				temp = _rows[i].at(k);
				if(temp == _empty){
					col = k;
					row = i;
					//std::cout << "leaving row loop" << std::endl;
					loc.push_back(row);
					loc.push_back(col);

					return loc;
				}

			}
		}
	}
	*/
	loc.push_back(row);
	loc.push_back(col);

	return loc;

}


std::string Game::printBoardState(){
	std::string temp = "";

	for(int i = 0; i < _rowSize; i++){
		for(int k = 0; k < _rows[i].size(); k++){
			temp += std::to_string(_rows[i].at(k)) + " ";
		}
		temp += "\n";
	}

	return temp;
}

int Game::input(float row, float col, int in){
	if(_turn >= (_rowSize * _colSize)){
		//std::cout << "TIE" << std::endl;
		_tie = true;
		_p1Win = false;
		return 10;
	}
	if(_rows[row].at(col) >= 0){
		std::cout << "ALREADY PLAYED!!" << in << std::endl;
		return 3;
	}


	_turn++;
	_history.push_back(getRows());

	if(in == 2){
		_p1Moves.push_back({row, col});
		_p1History.push_back(getRows());
	}
	else{
		_p2Moves.push_back({row, col});
		_p2History.push_back(getRows());
	}
	_rows[row][col] = in;


	if(_turn >= _rowSize || _turn >= _colSize){
		//std::cout << "Checking if Win" << std::endl;
		int count = 0;


			if(_rows[row].at(col) > (-1 * _diagSize)){
				for(int i = 0; i < _colSize; i++){
					count += _rows[i].at(col);
				}
			}
			if(count == _colSize){
				//std::cout << "1 col" << std::endl;
				_p1Win = false;
				return 1;
			}
			if(count == (_colSize * 2)){
				//std::cout << "2 col" << std::endl;
				return 0;
			}
			count = 0;


			if(_rows[row].at(0) > (-1 * _diagSize)){
				for(int i = 0; i < _rowSize; i++){
					count += _rows[row].at(i);
				}
			}
			if(count == _rowSize){
				//std::cout << "1 row" << std::endl;
				_p1Win = false;
				return 1;
			}
			if(count == (_rowSize * 2)){
				//std::cout << "2 row" << std::endl;
				return 0;
			}

			count = 0;


			//count += _rows[0].at(0);
			for(int i = 0; i < _diagSize; i++){
				count += _rows[_rowSlope * i].at(_colSlope * i);
			}
			if(count == _diagSize){
				//std::cout << "1 diag ++" << std::endl;
				_p1Win = false;
				return 1;
			}
			if(count == (_diagSize * 2)){
				//std::cout << "2 diag ++" << std::endl;
				return 0;
			}

			count = 0;


			//count += _rows[_rowSize - 1].at(_colSize - 1);
			for(int i = (_colSize - 1), k = 0; i >= 0 && k <= (_rowSize - 1); i--, k++){
				count += _rows[_rowSlope * k].at(_colSlope * i);
			}
			if(count == _diagSize){
				//std::cout << "1 diag +-" << std::endl;
				_p1Win = false;
				return 1;
			}
			if(count == (_diagSize * 2)){
				//std::cout << "2 diag +-" << std::endl;
				return 0;
			}
	}

	return -1;
}

int Game::getTurn(){
	return _turn;
}

std::vector<std::vector<float>> Game::getWinningMoves(){
	std::vector<std::vector<float>> loc = _emptyRows;
	std::vector<std::vector<float>> out;
	std::vector<float> temp;

	if(_p1Win){
		for(int i = 0; i < _p1Moves.size(); i++){
			loc[_p1Moves[i].at(0)].at(_p1Moves[i].at(1)) = 1;
			for(int k = 0; k < loc.size(); k++){
				for(int l = 0; l < loc.at(k).size(); l++){
					temp.push_back(loc[k].at(l));
				}
			}
			out.push_back(temp);
			temp.clear();
		}
	}
	else{
		for(int i = 0; i < _p2Moves.size(); i++){
			loc[_p2Moves[i].at(0)].at(_p2Moves[i].at(1)) = 1;
			for(int k = 0; k < loc.size(); k++){
				for(int l = 0; l < loc.at(k).size(); l++){
					temp.push_back(loc[k].at(l));
				}
			}
			out.push_back(temp);
			temp.clear();
		}
	}


	return out;
}






/*
std::vector<std::vector<float>> Game::getWinningMoves(){
	std::vector<std::vector<float>> out;
	std::vector<std::vector<float>> loc;
	if(_p1Win){
		for(int i = 0; i < _p1Moves.size(); i++){
			//row
			if(_p1Moves[i].at(0) > 1){
				out.push_back({1.0, 1.0});
			}
			else if(_p1Moves[i].at(0) > 0){
				out.push_back({1.0, 0.0});
			}
			else{
				out.push_back({0.0, 0.0});
			}

			//column
			if(_p1Moves[i].at(1) > 1){
				out.push_back({1.0, 1.0});
			}
			else if(_p1Moves[i].at(1) > 0){
				out.push_back({1.0, 0.0});
			}
			else{
				out.push_back({0.0, 0.0});
			}
		}
		for(int i = 0; i < out.size(); i += 2){
			loc.push_back({out[i].at(0), out[i].at(1), out[i + 1].at(0), out[i + 1].at(1)});
		}

		return loc;
	}
	else{
		for(int i = 0; i < _p2Moves.size(); i++){
			//row
			if(_p2Moves[i].at(0) > 1){
				out.push_back({1.0, 1.0});
			}
			else if(_p2Moves[i].at(0) > 0){
				out.push_back({1.0, 0.0});
			}
			else{
				out.push_back({0.0, 0.0});
			}

			//column
			if(_p2Moves[i].at(1) > 1){
				out.push_back({1.0, 1.0});
			}
			else if(_p2Moves[i].at(1) > 0){
				out.push_back({1.0, 0.0});
			}
			else{
				out.push_back({0.0, 0.0});
			}
		}

		for(int i = 0; i < out.size(); i += 2){
			loc.push_back({out[i].at(0), out[i].at(1), out[i + 1].at(0), out[i + 1].at(1)});
		}

		return loc;
	}
}
*/

std::vector<std::vector<float>> Game::getHistory(){
	if(_p1Win){
		return _p1History;
	}
	else{
		return _p2History;
	}
}

void Game::clear(){
	_rows.clear();
	_p1History.clear();
	_p2History.clear();
	_history.clear();
	_p1Moves.clear();
	_p2Moves.clear();
	_p1Win = true;
	_turn = 0;
	_tie = false;

	std::vector<float> temp;
	for(int i = 0; i < _rowSize; i++){
		for(int k = 0; k < _colSize; k++){
			temp.push_back(_empty);
		}
		this->_rows.push_back(temp);
		temp.clear();
	}
	this->_p1History.push_back(getRows());
}

bool Game::checkTie(){
	return _tie;
}

bool Game::checkP1Win(){
	return _p1Win;
}
