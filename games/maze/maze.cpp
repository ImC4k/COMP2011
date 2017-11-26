#include <iostream>
#include "maze.h"

using namespace std;

Maze::Maze(){
  board = nullptr;
}

Maze::Maze(coordinates dimension, coordinates start_pt, coordinates exit_pt){
  board = new char* [dimension.row]; // create a board
  for(int i = 0; i < dimension.row; i++){
    board[i] = new char[dimension.col];
    for(int j = 0; j < dimension.col; j++){
      board[i][j] = '_';
    }
  }
  board[start_pt.row][start_pt.col] = 'S';
  board[exit_pt.row][exit_pt.col] = 'E';

  set_start_exit(start_pt, exit_pt);
  set_dimension(dimension);
}

Maze::~Maze(){
  for(int i = 0; i < dimension.row; i++){
    delete[] board[i];
    board[i] = nullptr;
  }
  delete[] board;
  board = nullptr;
}

void Maze::set_dimension(coordinates dimension){
  this->dimension.row = dimension.row;
  this->dimension.col = dimension.col;
}

int Maze::get_row(){
  return dimension.row;
}

int Maze::get_col(){
  return dimension.col;
}

void Maze::set_start_exit(coordinates start_pt, coordinates exit_pt){
 this->start_pt = start_pt;
 this->exit_pt = exit_pt;
}

coordinates Maze::get_start(){
  return start_pt;
}

coordinates Maze::get_exit(){
  return exit_pt;
}

bool Maze::add_wall(coordinates location){
  if(location.row >= dimension.row || location.col >= dimension.col){
    cout<<"cannot put wall outside the board!"<<endl;
    return false;
  }
  board[location.row][location.col] = WALL;
  return true;
}

void Maze::print_maze(){
  cout<<"\n******************"<<endl;
  cout<<'\t';
  for(int i = 0; i < dimension.row; i++){
    cout<<i<<'\t';
  }
  cout<<endl;
  for(int i = 0; i < dimension.row; i++){
    cout<<i<<'\t';
    for(int j = 0; j < dimension.col; j++){
      cout<<board[i][j]<<'\t';
    }
    cout<<endl;
  }
  cout<<"******************"<<endl<<endl;

}

char Maze::get_element(coordinates location){
  return board[location.row][location.col];
}

bool Maze::solve_maze(int row, int col, direction prev_d){
  if(row == exit_pt.row && col == exit_pt.col){
    board[row][col] = '*';
    // cout<<"reached here"<<endl;
    // print_maze();
    return true;
  }
  else{
    if(prev_d != UP && row + 1 < dimension.row && board[row + 1][col] != WALL){ // go down case
      if(solve_maze(row + 1, col, DOWN)){
        board[row][col] = '*';
        // print_maze();
        return true;
      }
    }
    if(prev_d != LEFT && col + 1 < dimension.col && board[row][col + 1] != WALL){ // go right case
      if(solve_maze(row, col + 1, RIGHT)){
        board[row][col] = '*';
        // print_maze();
        return true;
      }
    }
    if(prev_d != DOWN && row - 1 >= 0 && board[row - 1][col] != WALL){ // go up case
      if(solve_maze(row - 1, col, UP)){
        board[row][col] = '*';
        // print_maze();
        return true;
      }
    }
    if( prev_d != RIGHT && col - 1 >= 0 && board[row][col - 1] != WALL){ // go left case
      if(solve_maze(row, col - 1, LEFT)){
        board[row][col] = '*';
        // print_maze();
        return true;
      }
    }
  }
  return false;
}

void Maze::reset_board(int option){
  for(int i = 0; i < dimension.row; i++){
    for(int j = 0; j < dimension.col; j++){
      if(option == 2){ // clean path only
        if(board[i][j] == '*'){
          board[i][j] = '_';
        }
      }
      else if(option == 1){ // clean all
        board[i][j] = '_';
      }
      else return;
    }
  }
  board[get_start().row][get_start().col] = 'S';
  board[get_exit().row][get_exit().col] = 'E';
}
