//============================================================================
// Name        : Game.cpp
// Author      : Travis
// Version     :
// Copyright   : This is protected
// Description : Citrus Junior in C++, Ansi-style
//============================================================================


// '*' allows a variable to maintain manipulation when passed through a function
// '&' is to reference

// '*' stores address, '&' references the address

#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "globals.h"

#include "reader.h"
#include <math.h>
#include "nn.h"

#include "TicTacToe.h"

#include <process.h>



int main(){


	sf::Clock clock; //starts the clock
	Game game = Game(3, 3);
	Network network = Network(18, 36, 27, 9);

	std::vector<std::vector<float>> inArr;
	std::vector<std::vector<float>> outArr;

	std::vector<std::vector<float>> w = network.getWeights();
	std::vector<std::vector<float>> b = network.getBias();
	std::vector<std::vector<float>> o;

	std::vector<std::vector<float>> ww;
	std::vector<std::vector<float>> bb;
	std::vector<std::vector<float>> temps;

	Function func = SIGMOID;

	float learn = .5;

	const int count = 20;

	std::vector<float> randl;
	std::vector<float> sigl;
	bool running = true;


	/*
	while(running){
		randl = game.getRand();

		std::cout << game.printBoardState() << std::endl;
		int in = game.input(randl.at(0), randl.at(1), 2);

		if(in == 0){
			std::cout << "RANDOM(2) WINS!!" << std::endl;
			std::cout << game.printBoardState() << std::endl;
			running = false;
		}
		else if(in == -1){
			std::cout << game.printBoardState() << std::endl;
			sigl = game.getRand();
			in = game.input(sigl.at(0), sigl.at(1), 1);
			if(in == 1){
				std::cout << "SIGL(1) WINS!!" << std::endl;
				std::cout << game.printBoardState() << std::endl;
				running = false;
			}
			else{
				std::cout << "AHHH" << in << std::endl;
			}
		}
		else if(in == 10){
			running = false;
		}
	}


	std::cout << "TURNS: " << game.getTurn() << std::endl;

	//game.input(1,1,1);

	//std::cout << game.getBoardState();


	std::vector<std::vector<std::vector<float>>> history = game.getHistory();
	std::vector<float> board = game.getRows();
	std::vector<std::vector<float>> wMoves = game.getWinningMoves();

	std::vector<std::vector<float>> netMoves;
	*/


	/*
	o.push_back(network.forwardPassToo(func, board, w[0], b[0]));
	o.push_back(network.forwardPassToo(func, o[0] , w[1], b[1]));
	o.push_back(network.forwardPassToo(func, o[1] , w[2], b[2]));

	std::cout << "FINISHED" << std::endl;
	*/

	std::cout << std::endl<< "--Starting NN game--" << std::endl;


	running = true;
	while(running){

		randl = game.getRand();
		std::cout << game.printBoardState() << std::endl;
		int in = game.input(randl.at(0), randl.at(1), 2);

		if(in == 0){
			std::cout << "RANDOM(2) WINS!" << std::endl;
			std::cout << game.printBoardState() << std::endl;
			running = false;
		}
		else if(in == -1){
			std::cout << game.printBoardState() << std::endl;

			std::cout << "FORWARD PASS START: " << clock.getElapsedTime().asSeconds() << std::endl;
			o.push_back(network.forwardPassToo(func, game.getRows(), w[0], b[0]));
			o.push_back(network.forwardPassToo(func, o[0] , w[1], b[1]));
			o.push_back(network.forwardPassToo(func, o[1] , w[2], b[2]));
			std::cout << "FORWARD PASS END: " << clock.getElapsedTime().asSeconds() << std::endl;
			sigl = game.netInput(o[2]);
			std::cout << "sigl size:" << sigl.size() << std::endl;
			std::cout << "sigl out:" << sigl[0] << sigl[1] << sigl[2] << sigl[3] << std::endl;

			o.clear();
			//sigl = game.getRand();
			if(sigl.size() > 0){
				in = game.input(sigl.at(0), sigl.at(1), 1);
			}

			if(in == 1){
				std::cout << "SIGL(1) WINS!!!!!!" << std::endl;
				std::cout << game.printBoardState() << std::endl;
				running = false;
			}
			else if(in == 10){
				std::cout << "RESETING" << in << std::endl;
				game.clear();
			}
		}
		else if(in == 10){
			game.clear();
		}
	}

	std::cout << std::endl << "!---FINISHED NN GAME---!" << std::endl;


	std::vector<std::vector<float>> history = game.getHistory();
	std::vector<std::vector<float>> wMoves = game.getWinningMoves();
	std::cout << "INIT END" << wMoves.size() << " :: " << history.size() << std::endl;


	for(int i = 0; i < wMoves.size(); i++){
		o.push_back(network.forwardPassToo(func, history.at(i), w[0], b[0]));
		o.push_back(network.forwardPassToo(func, o[0] , w[1], b[1]));
		o.push_back(network.forwardPassToo(func, o[1] , w[2], b[2]));

		temps = network.backprop(wMoves[i], o, b, w, learn, history.at(i), func);
		o.clear();
		ww.clear();
		bb.clear();
		ww.push_back(temps[1]);
		ww.push_back(temps[3]);
		ww.push_back(temps[5]);
		bb.push_back(temps[0]);
		bb.push_back(temps[2]);
		bb.push_back(temps[4]);
	}

	std::cout << "TRAINING START2: " << clock.getElapsedTime().asSeconds() << std::endl;
	//MAIN LOOP HERE
	for(int i = 0; i < count; i++){
		for(int k = 0; k < 500000; k++){
			game.clear();
			//std::cout << k << "1111: " << std::endl;


			running = true;
			while(running){
				randl = game.getRand();
				//std::cout << game.printBoardState() << std::endl;
				int in = game.input(randl.at(0), randl.at(1), 2);

				if(in == 0){
					/////////std::cout << "RANDOM(2) WINS!" << std::endl;
					//std::cout << game.printBoardState() << std::endl;
					running = false;
				}
				else if(in == -1){
					//std::cout << game.printBoardState() << std::endl;
					std::vector<float> board = game.getRows();

					//std::cout << "FORWARD PASS START: " << clock.getElapsedTime().asSeconds() << std::endl;
					o.push_back(network.forwardPassToo(func, board, w[0], b[0]));
					o.push_back(network.forwardPassToo(func, o[0] , w[1], b[1]));
					o.push_back(network.forwardPassToo(func, o[1] , w[2], b[2]));
					//std::cout << "FORWARD PASS END: " << clock.getElapsedTime().asSeconds() << std::endl;
					sigl = game.netInput(o[2]);
					//std::cout << sigl.size() << std::endl;

					o.clear();
					//sigl = game.getRand();
					//std::cout << "THING1" << std::endl;
					if(sigl.size() > 0){
						in = game.input(sigl.at(0), sigl.at(1), 1);
						//std::cout << "THING2" << std::endl;
					}

					//std::cout << "INPUT COMPLETE!" << std::endl;
					if(in == 1){
						/////////std::cout << "SIGL(1) WINS!!!!!!" << std::endl;
						//std::cout << game.printBoardState() << std::endl;
						running = false;
					}
					else if(in == 10){
						//std::cout << "TIE, CONTINUING" << std::endl;
						running = false;
					}
				}
				else if(in == 10){
					//std::cout << "TIE, CONTINUING" << std::endl;
					running = false;
				}
			}

			/*
			if(game.checkTie()){
				//std::cout << "TIE, CONTINUING" << std::endl;
				continue;
			}
			*/
			//std::cout << "NO TIE, CONTINUING" << std::endl;

			history = game.getHistory();
			wMoves = game.getWinningMoves();

			for(int i = 0; i < wMoves.size(); i++){

				o.push_back(network.forwardPassToo(func, history.at(i), w[0], b[0]));
				o.push_back(network.forwardPassToo(func, o[0], w[1], b[1]));
				o.push_back(network.forwardPassToo(func, o[1], w[2], b[2]));

				temps = network.backprop(wMoves[i], o, b, w, learn, history.at(i), func);
				ww.clear();
				bb.clear();
				ww.push_back(temps[1]);
				ww.push_back(temps[3]);
				ww.push_back(temps[5]);
				bb.push_back(temps[0]);
				bb.push_back(temps[2]);
				bb.push_back(temps[4]);
				o.clear();
			}
			w = ww;
			b = bb;



			/*
			o.clear();
			o.push_back(network.forwardPassToo(func, board, temps[1], temps[0]));
			o.push_back(network.forwardPassToo(func, o[0], temps[3], temps[2]));
			o.push_back(network.forwardPassToo(func, o[1], temps[5], temps[4]));
			ww.push_back(temps[1]);
			ww.push_back(temps[3]);
			ww.push_back(temps[5]);
			bb.push_back(temps[0]);
			bb.push_back(temps[2]);
			bb.push_back(temps[4]);

			temps.clear();
			temps = network.backprop(wMoves[0], o, bb, ww, learn, board, func);
			ww.clear();
			bb.clear();
			*/
		}
		std::cout << i << ": " << clock.getElapsedTime().asSeconds() << std::endl;
	}

	std::cout << std::endl<< "--Starting NN game--" << std::endl;
	int siglTrack = 0;
	int tieTrack = 0;
	for(int i = 0; i < 50; i++){

		game.clear();
		running = true;
		while(running){

			randl = game.getRand();
			std::cout << game.printBoardState() << std::endl;
			int in = game.input(randl.at(0), randl.at(1), 2);

			if(in == 0){
				std::cout << "RANDOM(2) WINS!" << std::endl;
				std::cout << game.printBoardState() << std::endl;
				running = false;
			}
			else if(in == -1){
				std::cout << game.printBoardState() << std::endl;

				std::cout << "FORWARD PASS START: " << clock.getElapsedTime().asSeconds() << std::endl;
				o.push_back(network.forwardPassToo(func, game.getRows(), w[0], b[0]));
				o.push_back(network.forwardPassToo(func, o[0] , w[1], b[1]));
				o.push_back(network.forwardPassToo(func, o[1] , w[2], b[2]));
				std::cout << "FORWARD PASS END: " << clock.getElapsedTime().asSeconds() << std::endl;
				sigl = game.netInput(o[2]);

				//std::cout << "SIGL0: " << o[2].at(0) << " | " << o[2].at(1) << std::endl << "SIGL1: " << o[2].at(2) << " | " << o[2].at(3)<< std::endl;
				//std::cout << "SIGL0: " << sigl[0] << " | " << sigl[1] << std::endl;

				o.clear();
				//sigl = game.getRand();
				if(sigl.size() > 0){

					in = game.input(sigl.at(0), sigl.at(1), 1);
				}
				if(in == 1){
					std::cout << "SIGL(1) WINS!!!!!!" << std::endl;
					siglTrack++;
					std::cout << game.printBoardState() << std::endl;
					running = false;
				}
				else if(in == 10){
					tieTrack++;
					running = false;
				}
				else{
					std::cout << "AHHH" << in << std::endl;
				}
			}
			else if(in == 10){
				tieTrack++;
				running = false;
			}
		}
	}



	std::cout << std::endl << "!---FINISHED NN GAME---! " << siglTrack << std::endl << tieTrack << std::endl;


	std::cout << "Game Ready!" << std::endl << std::endl;

	learn = 2;

	for(int i = 0; i < 50; i++){
		game.clear();
		running = true;
		int row;
		int col;
		while(running){
			std::cout << game.printBoardState() << std::endl;

			std::cout << "What is your row position? ";
			std::cin >> row;
			std::cout << "What is your col position? ";
			std::cin >> col;
			int in = game.input(row, col, 2);

			if(in == 0){
				std::cout << "PLAYER(2) WINS!" << std::endl;
				std::cout << game.printBoardState() << std::endl;
				running = false;
			}
			else if(in == -1){
				std::cout << game.printBoardState() << std::endl;

				std::cout << "FORWARD PASS START: " << clock.getElapsedTime().asSeconds() << std::endl;
				o.push_back(network.forwardPassToo(func, game.getRows(), w[0], b[0]));
				o.push_back(network.forwardPassToo(func, o[0] , w[1], b[1]));
				o.push_back(network.forwardPassToo(func, o[1] , w[2], b[2]));
				std::cout << "FORWARD PASS END: " << clock.getElapsedTime().asSeconds() << std::endl;
				sigl = game.netInput(o[2]);

				//std::cout << "SIGL0: " << o[2].at(0) << " | " << o[2].at(1) << std::endl << "SIGL1: " << o[2].at(2) << " | " << o[2].at(3)<< std::endl;
				//std::cout << "SIGL0: " << sigl[0] << " | " << sigl[1] << std::endl;

				o.clear();
				//sigl = game.getRand();
				if(sigl.size() > 0){

					in = game.input(sigl.at(0), sigl.at(1), 1);
				}
				if(in == 1){
					std::cout << "SIGL(1) WINS!!!!!!" << std::endl;
					siglTrack++;
					std::cout << game.printBoardState() << std::endl;
					running = false;
				}
				else{
					std::cout << "AHHH" << in << std::endl;
				}
			}
			else if(in == 10){
				tieTrack++;
				running = false;
			}
		}
		if(!game.checkTie()){
			history = game.getHistory();
			wMoves = game.getWinningMoves();

			for(int i = 0; i < wMoves.size(); i++){

				o.push_back(network.forwardPassToo(func, history.at(i), w[0], b[0]));
				o.push_back(network.forwardPassToo(func, o[0], w[1], b[1]));
				o.push_back(network.forwardPassToo(func, o[1], w[2], b[2]));

				temps = network.backprop(wMoves[i], o, b, w, learn, history.at(i), func);
				ww.clear();
				bb.clear();
				ww.push_back(temps[1]);
				ww.push_back(temps[3]);
				ww.push_back(temps[5]);
				bb.push_back(temps[0]);
				bb.push_back(temps[2]);
				bb.push_back(temps[4]);
				o.clear();
			}
			w = ww;
			b = bb;
		}

		std::cout << std::endl << "!---FINISHED PLAYER1 GAME---! " << siglTrack << std::endl << tieTrack << std::endl;
		game.clear();
		std::cout << "Game 2 Ready!" << std::endl << std::endl;

		running = true;
		int in;
		while(running){


			std::cout << game.printBoardState() << std::endl;

			std::cout << "FORWARD PASS START: " << clock.getElapsedTime().asSeconds() << std::endl;
			o.push_back(network.forwardPassToo(func, game.getRows(), w[0], b[0]));
			o.push_back(network.forwardPassToo(func, o[0] , w[1], b[1]));
			o.push_back(network.forwardPassToo(func, o[1] , w[2], b[2]));
			std::cout << "FORWARD PASS END: " << clock.getElapsedTime().asSeconds() << std::endl;
			sigl = game.netInput(o[2]);

			//std::cout << "SIGL0: " << o[2].at(0) << " | " << o[2].at(1) << std::endl << "SIGL1: " << o[2].at(2) << " | " << o[2].at(3)<< std::endl;
			//std::cout << "SIGL0: " << sigl[0] << " | " << sigl[1] << std::endl;

			o.clear();
			//sigl = game.getRand();
			if(sigl.size() > 0){

				in = game.input(sigl.at(0), sigl.at(1), 1);
			}

			if(in == 1){
				std::cout << "SIGL(2) WINS!" << std::endl;
				std::cout << game.printBoardState() << std::endl;
				running = false;
			}
			else if(in == -1){
				std::cout << game.printBoardState() << std::endl;

				std::cout << "What is your row position? ";
				std::cin >> row;
				std::cout << "What is your col position? ";
				std::cin >> col;
				int in = game.input(row, col, 2);

				if(in == 0){
					std::cout << "PLAYER(1) WINS!!!!!!" << std::endl;
					siglTrack++;
					std::cout << game.printBoardState() << std::endl;
					running = false;
				}
				else{
					std::cout << "AHHH" << in << std::endl;
				}
			}
			else if(in == 10){
				tieTrack++;
				running = false;
			}
		}
		if(!game.checkTie()){
			history = game.getHistory();
			wMoves = game.getWinningMoves();

			for(int i = 0; i < wMoves.size(); i++){

				o.push_back(network.forwardPassToo(func, history.at(i), w[0], b[0]));
				o.push_back(network.forwardPassToo(func, o[0], w[1], b[1]));
				o.push_back(network.forwardPassToo(func, o[1], w[2], b[2]));

				temps = network.backprop(wMoves[i], o, b, w, learn, history.at(i), func);
				ww.clear();
				bb.clear();
				ww.push_back(temps[1]);
				ww.push_back(temps[3]);
				ww.push_back(temps[5]);
				bb.push_back(temps[0]);
				bb.push_back(temps[2]);
				bb.push_back(temps[4]);
				o.clear();
			}
			w = ww;
			b = bb;
		}
	}





    return 0;
}
