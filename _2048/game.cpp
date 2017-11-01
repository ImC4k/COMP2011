#include <iostream>
#include "board.h"


using namespace std;

int main() {
	
	int size;
	cout << "Input the size of the board:";
	cin >> size;

	board *b = new board(size);
	char control = 'r';
	char rubbish = 'x';
	do {

		b->checkBoard();
		b->assignRandom();
		if (!b->checkBoard()) {
			break;
		}
		b->printBoard();
		cout << "Input direction:";
		cin >> control;
		switch (control)
		{
		case 'a':	b->updateBoard(LEFT); break;
		case 'd':	b->updateBoard(RIGHT); break;
		case 'w':	b->updateBoard(UP); break;
		case 's':	b->updateBoard(DOWN); break;
		}
		b->printBoard();
		cout << "input any thing to continue...";
		cin >> rubbish;
		b->checkBoard();
	}while (control != 'q' && !b->gameOver());

	b->printBoard();
	cout << endl << "????????????????????END????????????????????" << endl;

	return 0;
}