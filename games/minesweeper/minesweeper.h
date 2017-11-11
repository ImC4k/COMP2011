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
  bool is_gameover;
  char** information_board;
  char** hider_board;

public:
  minesweeper(void);                           // done
  ~minesweeper(void);                          // done
  void print_hider_board();                    // done
  void print_information_board();              // done
  void fill_board(const char);                 // done
  void place_bomb();                           // done
  void place_numbers();                        // done
  void flag_position(int, int);                // done
  void detonate_position(int, int);
  void copy_position(int, int);                // NOTE: for copying the char in information_board to hider_board
  void replace_position(int, int, char);
  void end_game_reveal();

};

#endif
