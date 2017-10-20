#include <iostream>

using namespace std;


const int BOARD_SIZE = 4; // we will assign BOARD_SIZE to
                          // different values (>=3) to test your program.
const char EMPTY = '.';  // symbol that represents an EMPTY spot
const char OCCUPIED = 'x'; // symbol that represents an OCCUPIED spot
enum direction {DOWN, RIGHT}; //a block is placed to right (RIGHT)  or downward (DOWN).


void placeBlock_recursion_part(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size, direction d, char content = OCCUPIED){
  if(size == 1){ // base case
    board[row][col] = content；
    }
  }
  else{
    board[row][col] = content;
    if(d == DOWN){
      placeBlock_recursion_part(board, row + 1, col, size - 1, d);
    }
    else{
      placeBlock_recursion_part(board, row, col + 1, size - 1, d);
    }
  }
  return;
}

bool find_local_place_recursion_part(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size, direction d){ // return true if no place
  cout<<"checking row = ["<<row<<"] col = ["<<col<<"]"<<endl;
  cout<<"size to be checked right now is "<<size<<endl;
  if(row < BOARD_SIZE){
    switch(d){
      case RIGHT:
        cout<<"running RIGHT direction"<<endl;
        if(col >= BOARD_SIZE){
          cout<<"exceeded boundary for RIGHT, returned true"<<endl;
          return true;
        }
        if(size == 1){
          cout<<"checking size == 1"<<endl;
          return !(board[row][col] == EMPTY);
        }
        else{
          if(board[row][col] == EMPTY){
            cout<<"size not yet 1, row = ["<<row<<"] col = ["<<col<<"] is EMPTY"<<endl;
            cout<<"commencing to obtain value of next element"<<endl;
            return find_local_place_recursion_part(board, row, col + 1, size - 1, d);
          }
          else return true;
        }
      case DOWN:
        cout<<"running DOWN direction"<<endl;
        if(row >= BOARD_SIZE){
          cout<<"exceeded boundary for DOWN, returned true"<<endl;
          return true;
        }
        if(size == 1){
          cout<<"checking size == 1"<<endl;
          return !(board[row][col] == EMPTY);
        }
        else{
          if(board[row][col] == EMPTY){
            cout<<"size not yet 1, row = ["<<row<<"] col = ["<<col<<"] is EMPTY"<<endl;
            cout<<"commencing to obtain value of next element"<<endl;
            return find_local_place_recursion_part(board, row + 1, col, size - 1, d);
          }
          else return true;
        }
    }
  }
  return true;
}

// Functions
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

void initBoard(char board[BOARD_SIZE][BOARD_SIZE], char filling = EMPTY) {
    for (int i = 0; i < BOARD_SIZE; i++)
	for (int j = 0; j < BOARD_SIZE; j++)
	    board[i][j] = filling;

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

// int getSmallestBlock(const int blocks[], int size) {
//   if(size == 0){
//     if(blocks[size] != 0){
//       return size;
//     }
//     else{
//       return BOARD_SIZE + 1;
//     }
//   }
//   else{
//     if(getSmallestBlock(blocks, size -1) != BOARD_SIZE + 1){
//       return getSmallestBlock(blocks, size -1);
//     }
//     else if(blocks[size] != 0){
//       return size;
//     }
//     else{
//       return BOARD_SIZE + 1;
//     }
//   }
// }
int getSmallestBlock(const int blocks[], int size) {
  if(size == 0){
    if(blocks[size] != 0){
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
 * If there is enough EMPTY spot to place the block, the function shall fill the locations of the board with
 * OCCUPIED (x) and it should return true to its caller.
 * If there is not enough EMPTY spot to place the block, or some part of the block is placed out of the game
 * board, the function shall not modify the board array and return false to its caller.
 *
 * You need to complete this function with recursion.
 */
bool placeBlock(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, direction d, int size) {
  if(size > BOARD_SIZE - ((d == RIGHT)? col : row)){
    return false;
  }
  switch(d){
    case RIGHT:
      if(!find_local_place_recursion_part(board, row, col, size, RIGHT)){
        placeBlock_recursion_part(board, row, col, size, d);
        return true;
      }
    case DOWN:
      if(!find_local_place_recursion_part(board, row, col, size, DOWN)){
        placeBlock_recursion_part(board, row, col, size, d);
        return true;
      }
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
bool cannotFitThisBlock(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size){
  // this function checks if there is any way to place a block of size "size"
  // update coordinate
  int update_coor_index = BOARD_SIZE*row + col;
  row = update_coor_index/BOARD_SIZE;
  col = update_coor_index%BOARD_SIZE;
  cout<<"update_coor_index is "<<update_coor_index<<endl;
  if(update_coor_index < BOARD_SIZE*BOARD_SIZE){ // if coordinate is still inside the board
    if(board[row][col] == EMPTY){
      if(!find_local_place_recursion_part(board, row, col, size, DOWN) || !find_local_place_recursion_part(board, row, col, size, RIGHT)){
        cout<<"row = ["<<row<<"] col = ["<<col<<"] returned false"<<endl;
        return false;
      }
    }
    else{
      cout<<"row = ["<<row<<"] col = ["<<col<<"] returned true"<<endl;
      cout<<"commencing to row = ["<<row<<"] col = ["<<col + 1<<"]"<<endl;
      return cannotFitThisBlock(board, row, col + 1, size);
    }
  }
  cout<<"every element ran, no result, returned true"<<endl;
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

// bool checkMate (char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col, direction& d, int blocks[BOARD_SIZE], int& size) {
//   // TODO problematic
//   blocks[size-1]--;
//
//   int temp = BOARD_SIZE*row + col;
//   if(temp > BOARD_SIZE*BOARD_SIZE){
//     return false;
//   }
//   row = temp/BOARD_SIZE;
//   col = temp%BOARD_SIZE;
//
//   if(getSmallestBlock(blocks, BOARD_SIZE) == BOARD_SIZE + 1){
//     return false;
//   }
//   if(placeBlock(board, row, col, DOWN, size)){
//     if(cannotFitThisBlock(board, row, col, getSmallestBlock(blocks, BOARD_SIZE))){
//       return true;
//     }
//   }
//   else if(placeBlock(board, row, col, RIGHT, size)){
//     if(cannotFitThisBlock(board, row, col, getSmallestBlock(blocks, BOARD_SIZE))){
//       return true;
//     }
//   }
//   else if(size < BOARD_SIZE){
//     blocks[size-1]++;
//     col += 1;
//     if(checkMate(board, row, col, d, blocks, size)){
//       return true;
//     }
//     col -= 1;
//     size += 1;
//     if(checkMate(board, row, col, d, blocks, size)){
//       return true;
//     }
//     size -= 1;
//   }
//
//   return false;
// }
bool checkMate (char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col, direction& d, int blocks[BOARD_SIZE], int& size) {
  blocks[size - 1]--;
  int update_coor_index = BOARD_SIZE*row + col;
  row = update_coor_index/BOARD_SIZE;
  col = update_coor_index%BOARD_SIZE;

  if(!cannotFitThisBlock(board, row, col, size)){
    placeBlock_recursion_part(board, row, col, size);
    if(cannotFitThisBlock(board, 0, 0, getSmallestBlock(blocks)))
  }

  else{
    checkMate(board, row, col + 1, d, size);
  }


  blocks[size - 1]++;
  return false;
}

int main(){
  char board[BOARD_SIZE][BOARD_SIZE];
  int blocks[BOARD_SIZE] = {2, 2, 2, 1};

    initBoard(board, OCCUPIED); // i modified this function, now the function will fill with OCCUPIED first
    printBoard(board);

    // and then I put some slots on the board
    board[0][3] = EMPTY;
    board[1][0] = EMPTY;
    board[1][2] = EMPTY;
    board[2][3] = EMPTY;
    board[3][0] = EMPTY;
    cout<<"\n\n\n";
    printBoard(board);
    cout<<boolalpha<<cannotFitThisBlock(board, 0, 0, 2);
    // cout<<getSmallestBlock(blocks, BOARD_SIZE)<<endl;
    // cout<<cannotFitThisBlock(board, 0, 0, getSmallestBlock(blocks, BOARD_SIZE))<<endl; // false
    // placeBlock(board, 3, 3, RIGHT, 2);
    // printBoard(board);
    // cout<<boolalpha<<placeBlock(board, 0, 0, RIGHT, 3)<<endl;
    // printBoard(board);
    // cout<<boolalpha<<findPlace_recursion_part(board, 0, 3, DOWN, 3)<<endl;
    // cout<<boolalpha<<placeBlock(board, 0, 3, DOWN, 3)<<endl;
    // printBoard(board);
    // cout<<"testing fit(7, 3, 3)\n"<<boolalpha<<cannotFitThisBlock(board, 7, 3, 3)<<endl; // true
    // printBoard(board);
  return 0;
}

//self-defined functions
