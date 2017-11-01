#include <iostream>
#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;



board::board(int size) {
	gameContinue = true;
	maxNum = 1;
	emptySize = size*size;
	this->size = size;
	this->arr = new int*[size];
	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
		for (int j = 0; j < size; j++) {
			arr[i][j] = 0;
		}
	}
	return;
}

board::~board() {
	if (arr != NULL) {
		for (int i = 0; i < size; i++) {
			if (arr[i] != NULL)
				delete[]arr[i];
			arr[i] = NULL;
		}
		delete []arr;
		arr = NULL;
	}
	return;
}

bool board::gameOver() {
	return !this->gameContinue;
}

void board::findEmpty() {
	int temp = size * size;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] != 0) {
				temp--;
			}
		}
	}
	emptySize = temp;
	return;
}

void board::printBoard() {
	findMaxNum();
	cout << "============PrintBoard===========" << endl;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] == 0)
				cout << ".\t";
			else
				cout << arr[i][j] << '\t';
		}
		cout << endl;
	}
	cout << "---------------------------------" << endl;
	cout << "Empty Size: " << emptySize << " | maxNum: 2^" << maxNum << " | gameContinue: ";
	if (gameContinue)
		cout << "True";
	else
		cout << "False";
	cout << endl;
	cout << "==========EndPrintBoard==========" << endl << endl;
	return;
}

void board::findMaxNum() {
	int tempMax = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] > tempMax) {
				tempMax = arr[i][j];
			}
		}
	}
	int tempIndex = 1;
	while (tempMax > 2) {
		tempMax /= 2;
		tempIndex++;
	}
	maxNum = tempIndex;
}

void board::assignRandom() {
	findMaxNum();
	findEmpty();
	if (!gameContinue)
		return;

	srand(time(0));
	int randBoardNum = pow(2.0, rand()%maxNum + 1);
	int randPutSize = (rand() % 2) + 1;
	if (emptySize < randPutSize) {
		randPutSize = emptySize;
	}

	for (int i = 0; i < randPutSize; i++) {
		int x;
		int y;
		do {
			x = rand() % size;
			y = rand() % size;
		} while (arr[x][y]!=0);
		arr[x][y] = randBoardNum;
		emptySize--;
	}

}

void board::updateBoard(direction d) {

	if (!gameContinue)
		return;

	//first push then add then push

	switch (d) {
	
	case UP:
		
		for (int x = 0; x < size; x++) {
			for (int i = 0; i < size; i++) {
				for (int j = size - 1; j >= 1; j--) {
					if (arr[j - 1][i] == 0 && arr[j][i] != 0) {
						arr[j - 1][i] = arr[j][i];
						arr[j][i] = 0;
					}
				}
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 1;) {
				if (arr[j][i] == arr[j + 1][i]) {
					arr[j + 1][i] = 2 * arr[j][i];
					arr[j][i] = 0;
					j += 2;
				}
				else
					j++;
			}
		}
		for (int x = 0; x < size; x++) {
			for (int i = 0; i < size; i++) {
				for (int j = size - 1; j >= 1; j--) {
					if (arr[j - 1][i] == 0 && arr[j][i] != 0) {
						arr[j - 1][i] = arr[j][i];
						arr[j][i] = 0;
					}
				}
			}
		}

		break;

	case DOWN:

		for (int x = 0; x < size; x++) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size - 1; j++) {
					if (arr[j + 1][i] == 0 && arr[j][i] != 0) {
						arr[j + 1][i] = arr[j][i];
						arr[j][i] = 0;
					}
				}
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = size - 1; j >= 1;) {
				if (arr[j][i] == arr[j - 1][i]) {
					arr[j - 1][i] = 2 * arr[j][i];
					arr[j][i] = 0;
					j -= 2;
				}
				else
					j--;
			}
		}
		for (int x = 0; x < size; x++) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size - 1; j++) {
					if (arr[j + 1][i] == 0 && arr[j][i] != 0) {
						arr[j + 1][i] = arr[j][i];
						arr[j][i] = 0;
					}
				}
			}
		}

		break;

	case LEFT: 

		for (int x = 0; x < size; x++) {
			for (int i = 0; i < size; i++) {
				for (int j = size - 1; j >= 1; j--) {
					if (arr[i][j - 1] == 0 && arr[i][j] != 0) {
						arr[i][j - 1] = arr[i][j];
						arr[i][j] = 0;
					}
				}
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 1;) {
				if (arr[i][j] == arr[i][j + 1]) {
					arr[i][j + 1] = arr[i][j] * 2;
					arr[i][j] = 0;
					j += 2;
				}
				else
					j++;
			}
		}
		for (int x = 0; x < size; x++) {
			for (int i = 0; i < size; i++) {
				for (int j = size - 1; j >= 1; j--) {
					if (arr[i][j - 1] == 0 && arr[i][j] != 0) {
						arr[i][j - 1] = arr[i][j];
						arr[i][j] = 0;
					}
				}
			}
		}

		break;


	case RIGHT:


		for (int x = 0; x < size; x++) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size - 1; j++) {
					if (arr[i][j + 1] == 0 && arr[i][j] != 0) {
						arr[i][j + 1] = arr[i][j];
						arr[i][j] = 0;
					}
				}
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = size - 1; j >= 1;) {
				if (arr[i][j] == arr[i][j - 1]) {
					arr[i][j - 1] = arr[i][j] * 2;
					arr[i][j] = 0;
					j -= 2;
				}
				else
					j--;
			}
		}
		for (int x = 0; x < size; x++) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size - 1; j++) {
					if (arr[i][j + 1] == 0 && arr[i][j] != 0) {
						arr[i][j + 1] = arr[i][j];
						arr[i][j] = 0;
					}
				}
			}
		}

		break;

	}
	findMaxNum();
	findEmpty();
	return;
}

bool board::checkBoard() {

	//return false if no emptySize
	findEmpty();
	if (emptySize) {
		gameContinue = true;
		return true;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			//check the one on top
			if ((i - 1) >= 0) {
				if (arr[i][j] == arr[i - 1][j]) {
					gameContinue = true;
					return true;
				}
			}
			//check the one down
			if ((i + 1) < size) {
				if (arr[i][j] == arr[i + 1][j]) {
					gameContinue = true;
					return true;
				}
			}
			//check the one on left
			if ((j - 1) >= 0) {
				if (arr[i][j] == arr[i][j - 1]) {
					gameContinue = true;
					return true;
				}
			}
			//check the one on right
			if ((j + 1) < size) {
				if (arr[i][j] == arr[i][j + 1]) {
					gameContinue = true;
					return true;
				}
			}
		}
	}
	gameContinue = false;
	return false;
}


