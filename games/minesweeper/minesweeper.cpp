#include "minesweeper.h"


minesweeper::minesweeper(){
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
  place_bomb();
  place_numbers();

  this->hider_board = new char*[height]; // create a 2d pointer array to store hider board
  for(int i = 0; i < height; i++){
    hider_board[i] = new char[width];
    for(int j = 0; j < width; j++){
      hider_board[i][j] = HIDDEN;
    }
  }
}

minesweeper::~minesweeper(){
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

void minesweeper::place_numbers(){
  for(int i = 0; i < this->board_height; i++){
    for(int j = 0; j < this->board_width; j++){
      if(information_board[i][j] == BOMB) continue;
      int neighbour_bomb_count = 0;
      for(int si = i-1; si <= i+1; si++){
        if(si < 0 || si >= this->board_height) continue;
        for(int sj = j-1; sj <= j+1; sj++){
          if(sj < 0 || sj >= this->board_width) continue;
          if(information_board[si][sj] == BOMB){
            neighbour_bomb_count++;
          }
        }
      }
      switch(neighbour_bomb_count){
        case 1: information_board[i][j] = '1'; break;
        case 2: information_board[i][j] = '2'; break;
        case 3: information_board[i][j] = '3'; break;
        case 4: information_board[i][j] = '4'; break;
        case 5: information_board[i][j] = '5'; break;
        case 6: information_board[i][j] = '6'; break;
        case 7: information_board[i][j] = '7'; break;
        case 8: information_board[i][j] = '8'; break;
        default: information_board[i][j] = BLANK;
      }
    }
  }
}

void minesweeper::flag_position(int x, int y){
  if(hider_board[y][x] == FLAG){
    hider_board[y][x] = HIDDEN;
  }
  else if(hider_board[y][x] != HIDDEN){
    return;
  }
  else hider_board[y][x] = FLAG;
}

void minesweeper::detonate_position(int x, int y){
  if(hider_board[y][x] == FLAG || hider_board[y][x] != HIDDEN){ // wont detonate any flagged positions, nor positions that were detonated
    return;
  }
  
}
