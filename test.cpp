#include <iostream>

using namespace std;

const int BOARD_SIZE = 9;
const int SIZE = 3;

bool check_single_region(int board[][BOARD_SIZE], int i, int j){// (i, j) are target location, (scanI, scanJ) are search start location
  // target = board[i][j];
  int scanI, scanJ;

  if(i<3) scanI = 0;
  else if(i<6) scanI = 3;
  else scanI = 6;

  if(j<3) scanJ = 0;
  else if(j<6) scanJ = 3;
  else scanJ = 6;

  for(int m = scanI; m < scanI+3; m++){
    for(int n = scanJ; n < scanJ+3; n++){
      if(m==i && n==j){
        continue;
      }
      if(board[m][n] == board[i][j]){
        // debug
        // cout<<"region check"<<endl;
        // cout<<"i = "<<i<<" j = "<<j<<" m = "<<m<<" n = "<<n<<endl;
        // cout<<"board[m][n] = "<<board[m][n]<<" board[i][j] = "<<board[i][j]<<endl;
        // debug end
        return false;
      }
    }
  }
  return true;
}

bool check_every_region(int board[][BOARD_SIZE]){
  // i += 3; j += 3; <-inside for-loop, consider 3x3 grids' coor.
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      if(!(check_single_region(board, i, j))){
        return false;
      }
    }
  }
  return true;
}

// check row functions
bool check_single_row(int board[][BOARD_SIZE], int i, int j){ // this can be used in task 2 too
  // target = board[i][j];
  for(int k = 0; k<BOARD_SIZE; k++){ // check row index, actually can skip check previous items
    if(k==j){
      continue;
    }
    if(board[i][k] == board[i][j]){
      // debug
      // cout<<"row check"<<endl;
      // cout<<"i = "<<i<<" k = "<<k<<" j = "<<j<<endl;
      // cout<<"board[i][k] = "<<board[i][k]<<" board[i][j] = "<<board[i][j]<<endl;
      // debug end
      return false;
    }
  }
  return true;
}

bool check_every_row(int board[][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      if(!check_single_row(board, i, j)){ // if false, then return false
        return false;
      }
    }
  }
  return true;
}

// check column functions
bool check_single_column(int board[][BOARD_SIZE], int i, int j){ // this can be used in task 2 too
  // target = board[i][j];
  for(int k = 0; k<BOARD_SIZE; k++){ // check column index, actually can skip checking previous items
    if(k==i){
      continue;
    }
    if(board[k][j] == board[i][j]){
      // debug
      // cout<<"column check"<<endl;
      // cout<<"k = "<<k<<" j = "<<j<<" i = "<<i<<endl;
      // cout<<"board[k][j] = "<<board[k][j]<<" board[i][j] = "<<board[i][j]<<endl;
      // debug end
      return false;
    }
  }
  return true;
}

bool check_every_column(int board[][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      if(!check_single_row(board, i, j)){ // if false, then return false
        return false;
      }
    }
  }
  return true;
}

// for task 2, check region, row, column for single element
bool check_element_condition(int board[][BOARD_SIZE], int i, int j){
  return check_single_region(board, i, j) && check_single_row(board, i, j) && check_single_column(board, i, j);
}


// Skeleton code

bool check_solution(int board[][BOARD_SIZE]){
  // TODO done
  if(check_every_row(board) && check_every_row(board) && check_every_column(board)){
    return true;
  }
  return false;
}

bool solve(int board[][BOARD_SIZE], int i, int j){
  // TODO
  if(i == BOARD_SIZE && j == BOARD_SIZE){ // reaching bottom most (base case)
    return true;
  }
  if(i < BOARD_SIZE && j >= BOARD_SIZE){
    i += 1;
    j = 0;
  }

  if(board[i][j] !=0){
    return solve(board, i, j+1);
  }
  
  int k = 1;
  while(true){
    board[i][j] = k;
    if(check_element_condition(board, i, j) && solve(board, i, j+1)){
      return true;
    }
    else if(!check_element_condition(board, i, j) && k == 9){
      return false;
    }
    else{
      k++;
    }
  }
}

bool solve_sudoku(int board[][BOARD_SIZE]){
    return solve(board, 0, 0);
}

void print_board(int board[][BOARD_SIZE]){
    cout << "Sudoku board" << endl;
    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j)
            cout << (j ? " " : "") << board[i][j];
        cout << endl;
    }
}



int main(){
  int board[BOARD_SIZE][BOARD_SIZE] = {{0,0,9,7,4,8,0,0,0},
                                        {7,0,0,0,0,0,0,0,0},
                                        {0,2,0,1,0,9,0,0,0},
                                        {0,0,7,0,0,0,2,4,0},
                                        {0,6,4,0,1,0,5,9,0},
                                        {0,9,8,0,0,0,3,0,0},
                                        {0,0,0,8,0,3,0,2,0},
                                        {0,0,0,0,0,0,0,0,6},
                                        {0,0,0,2,7,5,9,0,0}};
  int simpler_board[SIZE][SIZE] = { {1,0,2},
                                    {0,4,0},
                                    {7,0,0}
                                  };
  print_board(board);
  bool truth = solve_sudoku(board);
  print_board(board);
  cout<<boolalpha<<truth<<endl;
  return 0;
}
