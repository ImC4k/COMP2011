#include "minesweeper.h"


minesweeper::minesweeper(void){
  continue_game = true;
  int width, height, num_bomb;
  cout<<"Input board dimension (width, height): "<<endl;
  cin>>width>>height;
  this->board_width = width;
  this->board_height = height;

  cout<<"Input bombs you want to place: "<<endl;
  cin>>num_bomb;
  this->num_bomb = num_bomb;

  this->information_board = new char*[height]; // create a 2d pointer array to store information board
  for(int i = 0; i < height; i++){
    information_board[i] = new char[width];
    for(int j = 0; j < width; j++){
      information_board[i][j] = BLANK;
    }
  }
  this->hider_board = new char*[height]; // create a 2d pointer array to store hider board
  for(int i = 0; i < height; i++){
    hider_board[i] = new char[width];
    for(int j = 0; j < width; j++){
      hider_board[i][j] = HIDDEN;
    }
  }
}

minesweeper::~minesweeper(void){
  delete this->information_board;
  this->information_board = nullptr;
}

void minesweeper::print_hider_board(){
  for(int i = 0; i < this->board_height; i++){
    for(int j = 0; j < this->board_width; j++){
      cout<<hider_board[i][j]<<"\t";
    }
    cout<<endl;
  }
}

void minesweeper::print_information_board(){
  for(int i = 0; i < this->board_height; i++){
    for(int j = 0; j < this->board_width; j++){
      cout<<information_board[i][j]<<"\t";
    }
    cout<<endl;
  }
}

void minesweeper::fill_board(char filling){
  for(int i = 0; i < this->board_height; i++){
    for(int j = 0; j < this->board_width; j++){
      information_board[i][j] = filling;
    }
  }
}

void minesweeper::place_bomb(){
  int bomb_count = this->num_bomb;
  while(bomb_count){
    srand(time(NULL));
    int x_pos = rand()%(this->board_width);
    srand(time(NULL));
    int y_pos = rand()%(this->board_height);
    if(information_board[y_pos][x_pos] == BOMB){
      continue;
    }
    else{
      information_board[y_pos][x_pos] = BOMB;
      bomb_count--;
    }
  }
}
