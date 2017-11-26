#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>

const char WALL = 'X';
const char PATH = '*';

enum direction{DOWN, RIGHT, UP, LEFT, VOID};

struct coordinates{
  int row;
  int col;
};

class Maze{
private:
  coordinates dimension; // stores dimension of the board
  coordinates start_pt;
  coordinates exit_pt;
  char** board; // dynamic array to store board with dimesion: dimension
public:
  Maze();
  Maze(coordinates dimension, coordinates start_pt, coordinates exit_pt);
  ~Maze(); // manually destroy dynamic objects
  void set_dimension(coordinates dimension);
  int get_row();
  int get_col();
  void set_start_exit(coordinates start_pt, coordinates exit_pt);
  coordinates get_start();
  coordinates get_exit();
  bool add_wall(coordinates location); // add a wall if the given location is in the board
  char get_element(coordinates location);
  void print_maze();
  bool solve_maze(int row, int col, direction d);
  void reset_board(int option = 1); // option 1: clean all; 2: clean path only
};
#endif

// TODO randomly create walls
// TODO try to turn things into pointers for better memory management
