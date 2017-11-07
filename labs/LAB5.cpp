#include <iostream>

using namespace std;

const int GAMEBOARDSIZE = 18; // width and height of the game board

const int SAMPLEGAMEBOARD[GAMEBOARDSIZE][GAMEBOARDSIZE] = {
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const int GLIDER[GAMEBOARDSIZE][GAMEBOARDSIZE] = {
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const int PULSAR[GAMEBOARDSIZE][GAMEBOARDSIZE] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const int DIEHARD[GAMEBOARDSIZE][GAMEBOARDSIZE] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

// TODO: print game board specified
// finished
void printGameBoard(const int gameBoard[][GAMEBOARDSIZE]) {
	for(int i = 0; i< GAMEBOARDSIZE; i++){
		for(int j = 0; j< GAMEBOARDSIZE; j++){
			if(gameBoard[i][j])
				cout<<'X';
			else
				cout<<' ';
		}
		cout<<endl;
	}
}

// TODO: Set all cells in the game board to be dead
void initGameBoard(int gameBoard[][GAMEBOARDSIZE]) {
	for(int i = 0; i< GAMEBOARDSIZE; i++){
		for(int j = 0; j< GAMEBOARDSIZE; j++){
			gameBoard[i][j] = 0;
		}
	}
}

// TODO: Copy states of all cells from src to dst
void copyGameBoard(int dst[][GAMEBOARDSIZE], const int src[][GAMEBOARDSIZE]) {
	for(int i = 0; i< GAMEBOARDSIZE; i++){
		for(int j = 0; j< GAMEBOARDSIZE; j++){
			dst[i][j] = src[i][j];
		}
	}
}

// TODO: Return the number of live neighbors of cell gameBoard[x][y]
int getLiveNeighbors(const int gameBoard[][GAMEBOARDSIZE], int x, int y) {

	int neighbors = 0;
	// YOUR CODE:

	for(int i = x-1; i <= x+1; i++){
		for(int j = y-1; j<= y+1; j++){
			int scan_x;
			int scan_y;

			if(i < 0) scan_x = GAMEBOARDSIZE-1;
			else if(i > GAMEBOARDSIZE-1) scan_x = 0;
			else scan_x = i;

			if(j < 0) scan_y = GAMEBOARDSIZE-1;
			else if(j > GAMEBOARDSIZE-1) scan_y = 0;
			else scan_y = j;

			if(gameBoard[scan_x][scan_y] == 1){
				neighbors += 1;
			}
		}
	}
	if(gameBoard[x][y] == 1) neighbors -= 1;
	return neighbors;
}

// TODO: Update the game board according to the rules described
// HINT: Create a temporary game board
void updateGameBoard(int gameBoard[][GAMEBOARDSIZE]) {
	int tempGameBoard[GAMEBOARDSIZE][GAMEBOARDSIZE];
	initGameBoard(tempGameBoard);
	for(int i = 0; i < GAMEBOARDSIZE; i++){
		for(int j = 0; j < GAMEBOARDSIZE; j++){
			int neighbors = getLiveNeighbors(gameBoard, i, j);
			if(gameBoard[i][j] == 1 && neighbors < 2) tempGameBoard[i][j] = 0;
			else if(gameBoard[i][j] == 1 && (neighbors == 2 || neighbors == 3)) tempGameBoard[i][j] = 1;
			else if(gameBoard[i][j] == 1 && neighbors > 3) tempGameBoard[i][j] = 0;
			else if(gameBoard[i][j] == 0 && neighbors == 3) tempGameBoard[i][j] = 1;
		}
	}
	copyGameBoard(gameBoard, tempGameBoard);
}

void testPrintGameBoard() {
	printGameBoard(SAMPLEGAMEBOARD);
}

void testInitCopyGameBoard() {
	int gameBoard[GAMEBOARDSIZE][GAMEBOARDSIZE];

	initGameBoard(gameBoard);
	cout << "After init:" << endl;
	printGameBoard(gameBoard);

	copyGameBoard(gameBoard, SAMPLEGAMEBOARD);
	cout << "After copy:" << endl;
	printGameBoard(gameBoard);
}

void testGetLiveNeighbors() {

	printGameBoard(SAMPLEGAMEBOARD);

	cout << "Number of live neighbors of SAMPLEGAMEBOARD[0][0]: " << getLiveNeighbors(SAMPLEGAMEBOARD, 0, 0) << endl;
	cout << "Number of live neighbors of SAMPLEGAMEBOARD[1][1]: " << getLiveNeighbors(SAMPLEGAMEBOARD, 1, 1) << endl;
}

void testUpdateGameBoard() {

	int tempGameBoard[GAMEBOARDSIZE][GAMEBOARDSIZE];
	copyGameBoard(tempGameBoard, SAMPLEGAMEBOARD);

	cout << "Before update:" << endl;
	printGameBoard(tempGameBoard);
	cout << "After update:" << endl;
	updateGameBoard(tempGameBoard);
	printGameBoard(tempGameBoard);
}

void runGameBoard(const int gameBoard[][GAMEBOARDSIZE]) {

	char option;

	int tempGameBoard[GAMEBOARDSIZE][GAMEBOARDSIZE];

	copyGameBoard(tempGameBoard, gameBoard);

	printGameBoard(tempGameBoard);

	cout << "Continue? (y/N) ";
	cin >> option;

	while(option =='y') {
		updateGameBoard(tempGameBoard);
		printGameBoard(tempGameBoard);

		cout << "Continue? (y/N) ";
		cin >> option;
	}
}

void gallery() {

	while(true) {

		int option = 0;

		cout << "Gallery" << endl;
		cout << endl;

		cout << "1. Sample Game Board" << endl;
		cout << "2. Glider" << endl;
		cout << "3. Pulsar" << endl;
		cout << "4. Diehard" << endl;
		cout << "0. Go Back" << endl;

		cout << endl;

		cout << "Please select an option: ";
		cin >> option;

		switch(option) {
		case 1:
			runGameBoard(SAMPLEGAMEBOARD);
			break;
		case 2:
			runGameBoard(GLIDER);
			break;
		case 3:
			runGameBoard(PULSAR);
			break;
		case 4:
			runGameBoard(DIEHARD);
			break;
		case 0:
		default:
			return;
			break;
		}

		cout << endl;
	}
}

int main() {

	while(true) {

		int option = 0;

		cout << "Game of Life" << endl;
		cout << endl;

		cout << "1. Test: Print Game Board" << endl;
		cout << "2. Test: Init and Copy Game Board" << endl;
		cout << "3. Test: Get Live Neighbors" << endl;
		cout << "4. Test: Update Game Board" << endl;
		cout << "5. Gallery" << endl;
		cout << "0. Exit" << endl;

		cout << endl;

		cout << "Please select an option: ";
		cin >> option;

		switch(option) {
		case 1:
			testPrintGameBoard();
			break;
		case 2:
			testInitCopyGameBoard();
			break;
		case 3:
			testGetLiveNeighbors();
			break;
		case 4:
			testUpdateGameBoard();
			break;
		case 5:
			gallery();
			break;
		case 0:
		default:
			return 0;
			break;
		}

		cout << endl;
	}
}
