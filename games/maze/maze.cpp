#include "maze.h"

using namespace std;

Maze::Maze(){
  board = nullptr;
}

Maze::Maze(coordinates dimension, coordinates start_pt, coordinates exit_pt){ // normal constructor
  board = new char* [dimension.row]; // create a board
  for(int i = 0; i < dimension.row; i++){
    board[i] = new char[dimension.col];
    for(int j = 0; j < dimension.col; j++){
      board[i][j] = BLANK;
    }
  }
  board[start_pt.row][start_pt.col] = START;
  board[exit_pt.row][exit_pt.col] = EXIT;

  set_start_exit(start_pt, exit_pt);
  set_dimension(dimension);
}

Maze::Maze(string file_name){ // for directly importing a board from a file
  board = nullptr;

  ifstream input_file;
  input_file.open(file_name);

  int row_count = 0;

  while(!input_file.eof()){
    string trash;
    input_file>>trash;
    row_count++;
  }
  cout<<row_count<<endl;
  input_file.close();
  board = new char* [row_count];

  input_file.open(file_name);
  int col_count = -1;
  string temp_row_board;
  if(!input_file.eof()){
    input_file>>temp_row_board;
    col_count = temp_row_board.length();
  }
  board[0] = new char[col_count];
  for(int i = 0; i < col_count; i++){
    board[0][i] = temp_row_board[i];
  }
  cout<<row_count<<" "<<col_count<<endl;
  for(int i = 1; i < row_count; i++){
    // if(input_file.eof()){
    //   cout<<"something's wrong"<<endl;
    //   return;
    // }
    board[i] = new char[col_count];
    input_file>>temp_row_board;
    for(int j = 0; j < col_count; j++){
      board[i][j] = temp_row_board[j];
      if(board[i][j] == START){
        start_pt.row = i;
        start_pt.col = j;
      }
      else if(board[i][j] == EXIT){
        exit_pt.row = i;
        exit_pt.col = j;
      }
    }
  }
  input_file.close();
  dimension.row = row_count;
  dimension.col = col_count;
}

Maze::~Maze(){
  for(int i = 0; i < dimension.row; i++){
    delete[] board[i];
    // board[i] = nullptr;
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

void Maze::set_start_exit(coordinates start_pt, coordinates exit_pt){ // assign start and exit position
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

char Maze::get_element(coordinates location){
  return board[location.row][location.col];
}

void Maze::print_maze(){
  cout<<"\n******************"<<endl;
  cout<<'\t';
  for(int i = 0; i < dimension.col; i++){
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

void Maze::random_wall(int prob_reci){
  srand(time(NULL));
  for(int i = 0; i < dimension.row; i++){
    for(int j = 0; j < dimension.col; j++){
      if((i == start_pt.row && j == start_pt.col) || (i == exit_pt.row && j == exit_pt.col)){
        continue;
      }
      if(!(rand()%prob_reci)){
        board[i][j] = WALL;
      }
    }
  }
}

bool Maze::solve_maze(int row, int col, direction prev_d){
  if(row == exit_pt.row && col == exit_pt.col){
    board[row][col] = PATH;
    // cout<<"reached here"<<endl;
    // print_maze();
    return true;
  }
  else{
    board[row][col] = TEMP;
    if(prev_d != UP && row + 1 < dimension.row && board[row + 1][col] != WALL && board[row + 1][col] != TEMP){ // go down case
      if(solve_maze(row + 1, col, DOWN)){
        board[row][col] = PATH;
        // print_maze();
        return true;
      }
    }
    if(prev_d != LEFT && col + 1 < dimension.col && board[row][col + 1] != WALL && board[row][col + 1] != TEMP){ // go right case
      if(solve_maze(row, col + 1, RIGHT)){
        board[row][col] = PATH;
        // print_maze();
        return true;
      }
    }
    if(prev_d != DOWN && row - 1 >= 0 && board[row - 1][col] != WALL && board[row - 1][col] != TEMP){ // go up case
      if(solve_maze(row - 1, col, UP)){
        board[row][col] = PATH;
        // print_maze();
        return true;
      }
    }
    if( prev_d != RIGHT && col - 1 >= 0 && board[row][col - 1] != WALL && board[row][col - 1] != TEMP){ // go left case
      if(solve_maze(row, col - 1, LEFT)){
        board[row][col] = PATH;
        // print_maze();
        return true;
      }
    }
  }
  if(row == start_pt.row && col == start_pt.col){
    board[row][col] = START;
  }
  else{
    board[row][col] = BLANK;
  }
  return false;
}

void Maze::reset_board(int option){
  for(int i = 0; i < dimension.row; i++){
    for(int j = 0; j < dimension.col; j++){
      if(option == 2){ // clean path only
        if(board[i][j] == PATH){
          board[i][j] = BLANK;
        }
      }
      else if(option == 1){ // clean all
        board[i][j] = BLANK;
      }
      else return;
    }
  }
  board[get_start().row][get_start().col] = START;
  board[get_exit().row][get_exit().col] = EXIT;
}
