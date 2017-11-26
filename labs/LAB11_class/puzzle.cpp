#include <iostream>
#include <cstring>
#include "puzzle.h"
using namespace std;

/* Default constructor
 */
WordPuzzle::WordPuzzle()
{
   board = nullptr;
   size = 0;
}

// TODO 2: Implement the constructor to initialize a puzzle board of size n
WordPuzzle::WordPuzzle(int n){
  size = n;
  board = new char* [n]; // a pointer array
  for(int i = 0; i < n; i++){
    board[i] = new char[i+1]; // a char array
    for(int j = 0; j < i+1; j++){
      board[i][j] = '_';
    }
  }
}


/* Print the current state of the puzzle board
 */
void WordPuzzle::print()
{
   for (int i=0; i<size; i++)
   {
      for (int j=0; j<=i; j++)
      {
         cout << board[i][j];
         if (j!=i)
           cout << ",";
      }
      cout << endl;
   }
}

// TODO 3: Add a new word to the puzzle board at a specific position
bool WordPuzzle::add_word(const char* word, Position pos, Direction d){
  int len = strlen(word);
  int count = 0;
  int temp_row = pos.row, temp_col = pos.col;
  char content;

  while(count != len){ // check if the space i am accessing is valid: must be either '_' or same as the word's corr. alphabet
    if(temp_col > temp_row){
      return false;
    }
    char content = board[temp_row][temp_col];
    if(content != '_' && content != word[count]){
      return false;
    }

    count++;

    switch(d){
      case HORIZONTAL:
        temp_col++;
        break;

      case VERTICAL:
        temp_row++;
        break;

      case DIAGONAL:
        temp_col++;
        temp_row++;
        break;

      default: return false;
    }
  }

  count = 0;
  temp_row = pos.row, temp_col = pos.col;

  while(count != len){ // after checking every space needed, then place the entire word
    board[temp_row][temp_col] = word[count];
    count++;
    switch(d){
      case HORIZONTAL:
        temp_col++;
        break;

      case VERTICAL:
        temp_row++;
        break;

      case DIAGONAL:
        temp_col++;
        temp_row++;
        break;

      default: return false;
    }
  }
  return true;
}


/* Complete the empty positions of the puzzle board with random characters
 */
void WordPuzzle::complete_puzzle()
{
   for (int i=0; i<size; i++)
   {
      for (int j=0; j<=i; j++)
      {
         if (board[i][j] == '_')
            board[i][j] = 'a'+rand()%26;
      }
   }
}

// TODO 4:  Implement the destructor to deallocate the dyanmic puzzle
WordPuzzle::~WordPuzzle(){
  for(int i = 0; i < size; i++){
    delete[] board[i];
    board[i] = nullptr;
  }
  delete[] board;
  board = nullptr;
}
