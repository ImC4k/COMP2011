#include "minesweeper.h"


minesweeper::minesweeper(){
  this->continue_game = true;
  int width, height, num_bomb;
  cout<<"Input board dimension (width, height): "<<endl;
  cin>>width>>height;
  this->board_width = static_cast<int>(width);
  this->board_height = static_cast<int>(height);

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

  cout<<"Please wait for the board to generate"<<endl;
  place_bomb();
  place_numbers();
  cout<<"Done!"<<endl;
}

minesweeper::~minesweeper(){
  for(int i = 0; i < this->board_height; i++){
    delete[] information_board[i];
    information_board[i] = nullptr;
  }
  delete[] this->information_board;
  this->information_board = nullptr;
}

void minesweeper::get_dimension(int &height, int &width){
  height = this->board_height;
  width = this->board_width;
}

void minesweeper::print_hider_board(){
  cout<<"\t\t"; for(int i = 0; i < this->board_width; i++){ cout<<i; if(i != this->board_width) cout<<"\t";} cout<<endl;
  cout<<"\t\t"; for(int i = 0; i < this->board_width; i++){ cout<<"-\t";}cout<<endl;
  for(int i = 0; i < this->board_height; i++){
    cout<<i<<"\t|\t";
    for(int j = 0; j < this->board_width; j++){
      cout<<hider_board[i][j]<<"\t";
    }
    cout<<endl<<endl;
  }
}

void minesweeper::print_information_board(){
  cout<<"\t\t"; for(int i = 0; i < this->board_width; i++){ cout<<i; if(i != this->board_width) cout<<"\t";} cout<<endl;
  cout<<"\t\t"; for(int i = 0; i < this->board_width; i++){ cout<<"-\t";}cout<<endl;
  for(int i = 0; i < this->board_height; i++){
    cout<<i<<"\t|\t";
    for(int j = 0; j < this->board_width; j++){
      cout<<information_board[i][j]<<"\t";
    }
    cout<<endl<<endl;
  }
}

void minesweeper::fill_board(char filling){ // seems useless
  for(int i = 0; i < this->board_height; i++){
    for(int j = 0; j < this->board_width; j++){
      information_board[i][j] = filling;
    }
  }
}

void minesweeper::place_bomb(){
  int bomb_count = this->num_bomb;
  srand(time(NULL));
  while(bomb_count){
    int row = rand()%(this->board_height);
    srand(time(NULL));
    int col = rand()%(this->board_width);
    if(information_board[row][col] == BOMB){
      continue;
    }
    else{
      information_board[row][col] = BOMB;
      cout<<this->num_bomb-bomb_count<<". a bomb is in ["<<row<<"]["<<col<<"]"<<endl;
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
      // switch(neighbour_bomb_count){
      //   case 1: information_board[i][j] = '1'; break;
      //   case 2: information_board[i][j] = '2'; break;
      //   case 3: information_board[i][j] = '3'; break;
      //   case 4: information_board[i][j] = '4'; break;
      //   case 5: information_board[i][j] = '5'; break;
      //   case 6: information_board[i][j] = '6'; break;
      //   case 7: information_board[i][j] = '7'; break;
      //   case 8: information_board[i][j] = '8'; break;
      //   default: information_board[i][j] = BLANK;
      // }
      information_board[i][j] = '0' + neighbour_bomb_count;
    }
  }
}

void minesweeper::flag_position(int row, int col){
  if(hider_board[row][col] == FLAG){
    hider_board[row][col] = HIDDEN;
  }
  else if(hider_board[row][col] != HIDDEN){
    return;
  }
  else hider_board[row][col] = FLAG;
}

void minesweeper::copy_position(int row, int col){
  hider_board[row][col] = information_board[row][col];
}

void minesweeper::recursion_for_det_blank(int row, int col){ // TODO: segmentation fault 11, need to handle flagged case
  if(hider_board[row][col] == HIDDEN){
    switch(information_board[row][col]){
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8': copy_position(row, col); break;
      case BLANK:
        copy_position(row, col);
        for(int i = row-1; i <= row+1; i++){
          if(i < 0 || i >= this->board_height) continue;
          for(int j = col-1; j <= col+1; j++){
            if(j < 0 || j >= this->board_width) continue;
            recursion_for_det_blank(i, j);
          }
        }
      default: return;
    }
  }
}

void minesweeper::detonate_position(int row, int col){
  if(hider_board[row][col] == FLAG || hider_board[row][col] != HIDDEN){ // wont detonate any flagged positions, nor positions that were detonated
    return;
  }
  if(information_board[row][col] == BOMB){ // expose entire board, if bomb is flagged, keep the flag, if flagged wrong, turn to O; is_gameover set to true
    for(int i = 0; i < this->board_height; i++){
      for(int j = 0; j < this->board_width; j++){
        if(hider_board[i][j] == FLAG && information_board[i][j] == BOMB){
          continue;
        }
        else if(hider_board[i][j] == FLAG && information_board[i][j] != BOMB){
          hider_board[i][j] = 'O';
        }
        else copy_position(i,j);
      }
    }
    print_hider_board();
    cout<<"YOU'VE LOST"<<endl;
    this->continue_game = false;
    return;
  }
  else if(information_board[row][col] == BLANK){ // keep print neighbour until a number is hit or there is a bomb
    recursion_for_det_blank(row, col);
  }
  else if(information_board[row][col] == '1' || information_board[row][col] == '2' || information_board[row][col] == '3' || information_board[row][col] == '4' ||
   information_board[row][col] == '5' || information_board[row][col] == '6' || information_board[row][col] == '7' || information_board[row][col] == '8'){
     copy_position(row,col);
     return;
   }
}

bool minesweeper::is_finished_game(){
  // TODO
  for(int i = 0; i < this->board_height; i++){
    for(int j = 0; j < this->board_width; j++){
      if(information_board[i][j] == BOMB){
        continue;
      }
      if(information_board[i][j] != hider_board[i][j]){
        return false;
      }
    }
  }
  cout<<"\n\n"<<endl;
  print_hider_board();
  return true;
}

bool minesweeper::is_gameover(){
  return !this->continue_game;
}
