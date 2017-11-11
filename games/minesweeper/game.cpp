#include "minesweeper.h"

int main(){
  minesweeper* new_game = new minesweeper();
  cout<<"hider board: "<<endl;
  new_game->print_hider_board();
  cout<<"information board: "<<endl;
  // new_game->print_information_board();
  new_game->place_bomb();
  new_game->print_information_board();
}
