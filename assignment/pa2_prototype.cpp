/*
* 2017F COMP2011 PA2
* skeleton.cpp
*
*  Created on: Sep 20, 2017
*      Author: Kevin Wang
*/

#include <iostream>



using namespace std;



/**
* You should use the following const and enum whenever necessary. Do not hard code
* the size of game board, the char of an EMPTY spot and the char of an OCCUPIED spot.
*
*/
const int BOARD_SIZE = 4; // we will assign BOARD_SIZE to
// different values (>=3) to test your program.
const char EMPTY = '.';  // symbol that represents an EMPTY spot
const char OCCUPIED = 'x'; // symbol that represents an OCCUPIED spot
enum direction {DOWN, RIGHT}; //a block is placed to right (RIGHT)  or downward (DOWN).

// self-defined functions

void placeBlock_recursion_part(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size, direction d, char content = OCCUPIED){
  // cout<<"placeBlock_recursion_part: size now is "<<size<<endl;
  if(size == 1){ // base case
    board[row][col] = content; // change the element into content (default 'x')

  }
  else{
    board[row][col] = content;
    if(d == DOWN){
      placeBlock_recursion_part(board, row + 1, col, size - 1, d, content);
    }
    else{
      placeBlock_recursion_part(board, row, col + 1, size - 1, d, content);
    }
  }
  return;
}

bool find_local_place_recursion_part(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size, direction d){ // return true if no place
  if(row < BOARD_SIZE){ // check if recursion is out of boundary
    switch(d){
      case RIGHT:
      if(col >= BOARD_SIZE){ // check if recursion is out of boundary
        return true;
      }
      if(size == 1){
        return !(board[row][col] == EMPTY); // base case if element is empty, then return false
      }
      else{
        if(board[row][col] == EMPTY){ // not base case if element is empty, then check next element with size -1
          return find_local_place_recursion_part(board, row, col + 1, size - 1, d);
        }
        else return true; // if element is not EMPTY, then return true
      }
      case DOWN: // same logic with RIGHT
      if(row >= BOARD_SIZE){
        return true;
      }
      if(size == 1){
        return !(board[row][col] == EMPTY);
      }
      else{
        if(board[row][col] == EMPTY){
          return find_local_place_recursion_part(board, row + 1, col, size - 1, d);
        }
        else return true;
      }
    }
  }
  return true;
}


/**
* Given function. To print the game board.
* It is already completed. Do not modify it.
*/
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

/**
* Given function, to initialize a game board
* It is already completed. Do not modify it.
*/
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
* //UPDATED HERE @ 18/10/2017
* Example, assume the blocks array is {0, 1, 0, 2}; this should return 2;
*                 the blocks array is {2, 0, 0, 1}; this should return 1;
*                 the blocks array is {0, 0, 1, 2}; this should return 3; etc.
*
* Note, if the blocks array contains only 0s (all blocks are used), this should return BOARD_SIZE + 1.
*
*/
int getSmallestBlock(const int blocks[], int size) {
  // TODO finished
  if(size == 0){
    if(blocks[size] != 0){ // if there's something at blocks[0], then return size is 1 (size + 1 because size in this function means the array index)
      return size + 1;
    }
    else return BOARD_SIZE + 1;
  }
  else{
    int previous = getSmallestBlock(blocks, size - 1);
    if(previous != BOARD_SIZE + 1){
      return previous;
    }
    else if(blocks[size] != 0){
      return size + 1;
    }
    else return BOARD_SIZE + 1;
  }
  return 0;
}



/**
* @TODO function.
*
* This function takes the following parameters
* 1) char board[BOARD_SIZE][BOARD_SIZE] - a game board
* 2) int row, int col - the top-left corner of the position that you want to put a block
* 3) direction d, the direction you want to put a block, either downward (DOWN) or towards right (RIGHT)
* 4) the size of a block
*
* If there is enough empty spot to place the block, the function shall fill the locations of the board with
* OCCUPIED (x) and it should return true to its caller.
* If there is not enough empty spot to place the block, or some part of the block is placed out of the game
* board, the function shall not modify the board array and return false to its caller.
*
* You need to complete this function with recursion.
*/
bool placeBlock(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, direction d, int size) {
  if(size > BOARD_SIZE - ((d == RIGHT)? col : row)){ // check if the size of block will pass the wall of gameboard
    return false;
  }
  switch(d){
    case RIGHT:
    if(!find_local_place_recursion_part(board, row, col, size, RIGHT)){ // if there is space for the block,
      placeBlock_recursion_part(board, row, col, size, d); // then put the block
      return true;
    }
    break;
    case DOWN: // same logic as RIGHT
    if(!find_local_place_recursion_part(board, row, col, size, DOWN)){
      placeBlock_recursion_part(board, row, col, size, d);
      return true;
    }
    break;
  }
  return false;
}


/**
* @TODO function.
*
* You need to check if a player have any possible way to fit a block to the board.
* This function takes the input
* 1) board - the 2D array representing the board
* 2) row, col - two variables that may be useful to construct your recursion
* 3) size - the size of a block
*
* The function shall return true if there is NO anyway to fit a block to the board
* and return false if there is one or more than one way to fit a block into the board.
*
* When this function is called from the main program, we always fill the variable row
* and col as 0. But when you implement this function, these two parameter may be useful
* to construct your recursion.
*
*/
bool cannotFitThisBlock (char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size) {
  // TODO buggy
  // this function checks if there is any way to place a block of size "size"
  // update coordinate
  int update_coor_index = BOARD_SIZE*row + col;
  row = update_coor_index/BOARD_SIZE;
  col = update_coor_index%BOARD_SIZE;

  if(update_coor_index < BOARD_SIZE*BOARD_SIZE){ // if coordinate is still inside the board
    if(board[row][col] == EMPTY){
      if(!find_local_place_recursion_part(board, row, col, size, DOWN) || !find_local_place_recursion_part(board, row, col, size, RIGHT)){ // check the local element if there is space to put the block
        return false;
      }
    }
    return cannotFitThisBlock(board, row, col + 1, size); // if no place for this local element, then check the next element
  }
  return true;
}


/**
* @TODO
*
* This function should determine if there is any "checkmate move". A checkmate move is a valid move that
* if a player makes that move, his opponent will lose the game immediately. If there is such case, the
* function should return true and assign that move to the variables row, col, direction, size. If there is no
* "checkmate move" the function should return false and the reference variables should not be modified.
*
* Similar to the above functions, row and col should be representing the top-left corner of the position
* of the block and direction should be either RIGHT or DOWN that represents towards right or downward.
* The variable size is the size of the block and it is required there are still unused blocks of that size
* available, that is, blocks[size - 1] > 0.
*
* This function requires the status of board and the remaining number of blocks and they are supplied in the
* array board and blocks respectively. You can assume the size of these two arrays are always "correct" when
* it is tested. That is, you don't need to worry about if board or blocks have insufficient sizes and leading
* array out of bound.
*
* When this function is called in the main program or our testing code, the variables will be set as:
* row = 0, col = 0, direction = RIGHT, size = 1
*
* Note, it is possible to have more than one checkmate move. In this case you are required to assign ANY ONE
* of the checkmate moves into the variables row, col, direction, size.
*/

bool checkMate(char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col, direction& d, int blocks[BOARD_SIZE], int& size){
  if(row >= BOARD_SIZE){
    row = 0; col = 0; d = RIGHT; size = 1;
    return false;
  }
  if(size >=1 && size <= BOARD_SIZE){
    if(blocks[size - 1] == 0){
      return checkMate(board, row, col, d, blocks, ++size); // check next size
    }
    if(placeBlock(board, row, col, RIGHT, size)){
      blocks[size - 1]--;
      if(cannotFitThisBlock(board, 0, 0, getSmallestBlock(blocks, BOARD_SIZE))){
        d = RIGHT;
        blocks[size - 1]++;
        placeBlock_recursion_part(board, row, col, size, RIGHT, EMPTY);
        return true;
      }
      else{
        blocks[size - 1]++;
        placeBlock_recursion_part(board, row, col, size, RIGHT, EMPTY);
      }
    }
    if(placeBlock(board, row, col, DOWN, size)){
      blocks[size - 1]--;
      if(cannotFitThisBlock(board, 0, 0, getSmallestBlock(blocks, BOARD_SIZE))){
        d = DOWN;
        blocks[size - 1]++;
        placeBlock_recursion_part(board, row, col, size, DOWN, EMPTY);
        return true;
      }
      else{
        blocks[size - 1]++;
        placeBlock_recursion_part(board, row, col, size, DOWN, EMPTY);
      }
    }
    return checkMate(board, row, col, d, blocks, ++size);
  }
  else{
    size = 1;
    row = row + (col + 1)/BOARD_SIZE;
    col = (col + 1)%BOARD_SIZE;
    return checkMate(board, row, col, d, blocks, size);
  }
  return false;
}


int main() {
  char board[BOARD_SIZE][BOARD_SIZE];
  int blocks[BOARD_SIZE];
  int turn = 0; // 0 for player 1; 1 for player 2;

  //initialize game board
  initBoard(board);

  //initialize number blocks
  for (int i = 0; i < BOARD_SIZE - 1; i++) {
    blocks[i] = 2;
  }
  blocks[BOARD_SIZE - 1] = 1;


  do {
    cout << "It is your turn, player " << (turn + 1) << endl;
    printBoard(board);
    cout << "Remaining Blocks" << endl;
    for (int i = 0; i < BOARD_SIZE; i++)
    cout << (i+1) << " ";
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++)
    cout << blocks[i] << " ";
    cout << endl;

    int row = 0, col = 0;
    int size = 1;
    int d = 0;

    direction dir = RIGHT;
    if (checkMate(board, row, col, dir, blocks, size)) {
      cout << "There is check mate move: (" << row << ", " << col << "), place size " << size <<
      ((dir == RIGHT)? " to right": " down") << endl;
    }

    while (1) {
      cout << "Please enter the coordinate: row col" << endl;
      cin >> row >> col;
      if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
      break;
      cout << "Invalid input" << endl;
    }

    while (1) {
      cout << "Please enter the size of the block: (1 to "<< BOARD_SIZE <<")" << endl;
      cin >> size;
      if (size > 0 && size <= BOARD_SIZE && blocks[size - 1] != 0)
      break;
      cout << "Invalid input or block of that size are used up." << endl;
    }

    while (1) {
      cout << "Direction? 1 for Right, 0 for Down: " << endl;
      cin >> d;
      if (d == 0 || d == 1)
      break;
      cout << "Invalid input" << endl;
    }


    if (!placeBlock(board, row, col, static_cast<direction>(d) , size))
    cout << "Cannot place the block, please try again" << endl;
    else {
      turn = (turn + 1) % 2 ;
      blocks[size - 1]--;
    }
    if (getSmallestBlock(blocks, BOARD_SIZE) > BOARD_SIZE) {
      printBoard(board);
      cout << "Game over. Block completed. " << endl;
    }

  }  while(!cannotFitThisBlock (board, 0, 0, getSmallestBlock(blocks, BOARD_SIZE)));
  printBoard(board);
  cout << "Player " << (turn + 1) << ":no more move, game over!" << endl;

}
