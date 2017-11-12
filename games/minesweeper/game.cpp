#include "minesweeper.h"

int main(){
  minesweeper* new_game = new minesweeper();
  cout<<"------------debug------------"<<endl;
  cout<<"information board: "<<endl;
  new_game->print_information_board();
  cout<<"------------debug------------"<<endl;
  cout<<"\n\n\n\n\n"<<endl;
  // new_game->print_hider_board();
  cout<<"============MINESWEEPER============\n\n\n"<<endl;
  while(!new_game->is_gameover()){
    char toggle_f_and_d;
    int row, col;
    new_game->print_hider_board();
    cout<<"\nEnter \'f\' to flag a coordinate,\nEnter \'d\'to detonate a coordinate: "<<endl;
    cin>>toggle_f_and_d>> row >> col;
    switch(toggle_f_and_d){
      case 'f': new_game->flag_position(row, col); break;
      case 'd': new_game->detonate_position(row, col);
    }
    if(new_game->is_finished_game() && !new_game->is_gameover()){
      cout<<"YOU WON!"<<endl;
      break;
    }
  }
  cout<<"\n\n\nThanks for playing!"<<endl;
  return 0;
}
