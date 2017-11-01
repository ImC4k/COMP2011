#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

enum direction {UP, DOWN, LEFT, RIGHT};

class board {

private:
	int ** arr;			//store the array of the game
	int size;			//store the size of the gameBoard
	int emptySize;		//store the emptySize(.) of the board
	int maxNum;		//store the max num (x) of the array, e.g 2^x
	bool gameContinue;	//determine gameover or not


public:
	board(int size);				//initialize the game
	~board();						//destructor
	bool gameOver();				//return true if game is over
	void findEmpty();				//find empty space of the board
	void printBoard();				//print the game board
	void findMaxNum();				//find the maxNum of the array
	void assignRandom();			//assign a value randomly
	void updateBoard(direction d);	//update the game board with direction
	bool checkBoard();				//check whether has next move, return true if has next move

};

#endif // _BOARD_H_

