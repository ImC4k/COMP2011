#ifndef MINESWEEPER_H_
#define MINESWEEPER_H_
#include "utils.h"

const char BOMB = 'X';
const char HIDDEN = '#';
const char BLANK = ' ';
const char FLAG = '^';

class minesweeper{

private:
  int board_width;
  int board_height;
  int num_bomb;
  bool continue_game;

public:
  char** information_board;
  char** hider_board;
  minesweeper(void);
  ~minesweeper(void);
  void print_hider_board();
  void print_information_board();
  void fill_board(const char);
  void place_bomb();
  void dedonate_position(int, int);
  void flag_position(int, int);
  void replace_position(int, int, char);
  bool is_gameover(char**);
  void copy_position(int, int);

};

#endif
