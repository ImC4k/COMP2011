#include <iostream>
#include "maze.h"

using namespace std;

int main(){
RESTART:
  cout<<"Please input board dimension: "<<endl;;
  coordinates dimension;
  cin>>dimension.row>>dimension.col;
  cout<<"Use default start and exit point ( 0, 0 ) and ( "<<dimension.row-1<<", "<<dimension.col-1<<" ) ? y or n"<<endl;
  char default_points;
  cin>>default_points;

  coordinates start_pt = {0, 0}, exit_pt = {dimension.row-1, dimension.col-1};
  if(default_points == 'n'){
    cout<<"Please input wanted location of Start point and Exit point"<<endl;
    cin>>start_pt.row>>start_pt.col>>exit_pt.row>>exit_pt.col;
  }


  Maze* maze = new Maze(dimension, start_pt, exit_pt);

  int function_choice = -1;
while(function_choice != 0){
    cout<<"*******MAZE*******"<<endl<<endl;
    cout<<"enter 0 to quit program"<<endl;
    cout<<"enter 1 to print board"<<endl;
    cout<<"enter 2 to add wall"<<endl;
    // cout<<"enter 3 to randomly create board"<<endl;
    cout<<"enter 4 to solve maze"<<endl;
    cout<<"enter 5 to clean maze"<<endl;
    cout<<"enter 6 for new maze board"<<endl;
    cout<<"******************"<<endl<<endl;
    cin>>function_choice;
    switch(function_choice){
      case 1: // print board
        maze->print_maze();
        break;

      case 2: // add wall
        coordinates location;
        cout<<"please enter location you want to put a wall at: "<<endl;
        cin>>location.row>>location.col;
        maze->add_wall(location);
        break;

      case 3:
        cout<<"not developed yet!"<<endl;
        break;

      case 4:
        if(maze->get_element(maze->get_start()) == WALL || !maze->solve_maze(maze->get_start().row, maze->get_start().col, VOID)){ // useless direction if first placement
          cout<<"there is no solution to this board!"<<endl;
        }
        break;

      case 5:
        cout<<"clean option: 1 for entire board; 2 for path only"<<endl;
        int option;
        cin>>option;
        if(option == 1){
          maze->reset_board();
        }
        else if(option == 2){
          maze->reset_board(2);
        }
        break;

      case 6:
        delete maze;
        goto RESTART;

      default: break;
    }
  }

  return 0;
}
