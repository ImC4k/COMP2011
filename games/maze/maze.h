#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>

using namespace std;

const char WALL = 'X';
const char PATH = '*';
const char BLANK = '_';
const char TEMP = '?';
const char START = 'S';
const char EXIT = 'E';

enum direction{DOWN, RIGHT, UP, LEFT, VOID}; // VOID is designed for start of game, no previous direction

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
  Maze(string file_name);
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
  void random_wall(int probability_reciprical = 5); // can input a custom reciprical of probability of placing walls
  bool solve_maze(int row, int col, direction d);
  void reset_board(int option = 1); // option 1: clean all; 2: clean path only
};
#endif
