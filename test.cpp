#include <iostream>

using namespace std;


const int BOARD_SIZE = 4; // we will assign BOARD_SIZE to
                          // different values (>=3) to test your program.
const char EMPTY = '.';  // symbol that represents an EMPTY spot
const char OCCUPIED = 'x'; // symbol that represents an OCCUPIED spot
enum direction {DOWN, RIGHT}; //a block is placed to right (RIGHT)  or downward (DOWN).

void printBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "* ";
    for (int j = 0; j < BOARD_SIZE; j++)
	cout << (j % 10) << " ";
    cout << "* " << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
	cout << (i % 10) << " ";
	for (int j = 0; j < BOARD_SIZE; j++)
	    cout << board[i][j] << ' ';
	cout << "*" << endl;
    }
    for (int j = 0; j < BOARD_SIZE + 2; j++)
	cout << "* ";
    cout << endl;
}

void initBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
	for (int j = 0; j < BOARD_SIZE; j++)
	    board[i][j] = EMPTY;

}

/**
 * @TODO function
 *
 * You need to return the smallest block available to use from an input array.
 * This function takes two parameters:
 * 1) blocks - an array storing the number of blocks remains for each block size. For instance, blocks[0]
 * should store how many 'Size 1' blocks are remaining and blocks[4] should store how many 'Size 5' blocks are remaining.
 * 2) size - a variable that may be useful when constructing your recursion.
 *
 * When this function is called in the main program, the variable "size" is always set as BOARD_SIZE.
 *
 * Example, assume the blocks array is {0, 1, 0, 2}; this should return 1;
 *                 the blocks array is {2, 0, 0, 1}; this should return 0;
 *                 the blocks array is {0, 0, 1, 2}; this should return 2; etc.
 *
 * Note, if the blocks array contains only 0s (all blocks are used), this should return BOARD_SIZE + 1.
 *
 */
int getSmallestBlock(const int blocks[], int size) {
  if(size == 0){
    if(blocks[size] != 0){
      return size;
    }
    else{
      return BOARD_SIZE + 1;
    }
  }
  else{
    if(getSmallestBlock(blocks, size -1) != BOARD_SIZE + 1){
      return getSmallestBlock(blocks, size -1);
    }
    else if(blocks[size] != 0){
      return size;
    }
    else{
      return BOARD_SIZE + 1;
    }
  }
}

int main(){
  char board[BOARD_SIZE][BOARD_SIZE];
  int blocks[BOARD_SIZE] = {0,2,0,1};
  cout<<getSmallestBlock(blocks, BOARD_SIZE)<<endl;
  initBoard(board);
  printBoard(board);
  return 0;
}
