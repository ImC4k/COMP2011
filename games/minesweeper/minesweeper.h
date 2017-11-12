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
  char** information_board;
  char** hider_board;

public:
  minesweeper(void);                          // done
  ~minesweeper(void);                         // done
  void print_hider_board();                   // done
  void print_information_board();             // done
  void fill_board(const char);                // done NOTE: seems useless
  void place_bomb();                          // done
  void place_numbers();                       // done
  void flag_position(int, int);               // done
  void copy_position(int, int);               // done NOTE: use: copy the char from information_board to hider_board
  void recursion_for_det_blank(int, int);     // done NOTE: use: recursively find neighbour blank space to print
  void detonate_position(int, int);           // done
  bool is_finished_game();                    // done NOTE: check if every position except bombs are exposed
  bool is_gameover();                         // done

};

#endif
