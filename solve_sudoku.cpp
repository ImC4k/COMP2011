#include <iostream>

using namespace std;

// CONSTANTS
const int BOARD_SIZE = 9;
const int SIZE = 3;

const int board[BOARD_SIZE][BOARD_SIZE] = {{5,3,0,0,7,0,0,0,0},
                                      {6,0,0,1,9,5,0,0,0},
                                      {0,9,8,0,0,0,0,6,0},
                                      {8,0,0,0,6,0,0,0,3},
                                      {4,0,0,8,0,3,0,0,1},
                                      {7,0,0,0,2,0,0,0,6},
                                      {0,6,0,0,0,0,2,8,0},
                                      {0,0,0,4,1,9,0,0,5},
                                      {0,0,0,0,8,0,0,7,9}};

const int task1_board[BOARD_SIZE][BOARD_SIZE] = {{1,4,3,6,2,8,5,7,9},
                                    {5,7,2,1,3,9,4,6,8},
                                    {9,8,6,7,5,4,2,3,1},
                                    {3,9,1,5,4,2,7,8,6},
                                    {4,6,8,9,1,7,3,5,2},
                                    {7,2,5,8,6,3,9,1,4},
                                    {2,3,7,4,8,1,6,9,5},
                                    {6,1,9,2,7,5,8,4,3},
                                    {8,5,4,3,9,6,1,2,7}};

const int debug_board[BOARD_SIZE][BOARD_SIZE] = {{5,3,4,6,7,8,9,1,2},
                                    {6,7,2,1,9,5,3,4,8},
                                    {1,9,8,3,9,0,0,6,0},
                                    {8,0,0,0,6,0,0,0,3},
                                    {4,0,0,8,0,3,0,0,1},
                                    {7,0,0,0,2,0,0,0,6},
                                    {0,6,0,0,0,0,2,8,0},
                                    {0,0,0,4,1,9,0,0,5},
                                    {0,0,0,0,8,0,0,7,9}};


const int simpler_board[SIZE][SIZE] = { {1,0,2},
                                  {0,4,0},
                                  {7,0,0}
                                };



// FUNCTIONS
bool check_single_region(const int board[][BOARD_SIZE], int i, int j){// (i, j) are target location, (scanI, scanJ) are search start location
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

bool check_every_region(const int board[][BOARD_SIZE]){
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
bool check_single_row(const int board[][BOARD_SIZE], int i, int j){ // this can be used in task 2 too
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

bool check_every_row(const int board[][BOARD_SIZE]){
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
bool check_single_column(const int board[][BOARD_SIZE], int i, int j){ // this can be used in task 2 too
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

bool check_every_column(const int board[][BOARD_SIZE]){
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
bool check_element_condition(const int board[][BOARD_SIZE], int i, int j){
  return check_single_region(board, i, j) && check_single_row(board, i, j) && check_single_column(board, i, j);
}


// Skeleton code
// Task 1
bool check_solution(int board[][BOARD_SIZE]){
  // TODO done
  return check_every_region(board) && check_every_row(board) && check_every_column(board);
}

// Task 2
bool solve(int board[][BOARD_SIZE], int i, int j){
  // TODO
  // debug
  // cout<<"i = "<<i<<", j = "<<j<<endl;
  // debug end

  int temp = i*BOARD_SIZE+j;
  i = temp/BOARD_SIZE;
  j = temp%BOARD_SIZE;

  if(i >= BOARD_SIZE-1 && j >= BOARD_SIZE-1){ // reaching bottom most (base case)
    if(board[i][j] != 0){
      return true;
    }
    else{
      int k = 1;
      while(true){

        if(k > 9){
          board[i][j] = 0;
          return false;
        }
        board[i][j] = k;
        // debug
        // cout<<"\n\n\n\n\n\n\n";
        // void print_board(int[][BOARD_SIZE]);
        // print_board(board);
        // cout<<"i = "<<i<<", j = "<<j<<endl;
        //debug end

        // attempt newest
        if(check_element_condition(board, i, j)){
          return true;
        }
        else{
          k++;
          continue;
        }
      }
    }
  }

  else if(board[i][j] !=0){ // if already solved, then just give the answer of next element
    return solve(board, i, j+1);
  }

  else{
    int k = 1; // start the attempt by putting 1 through 9 to the 0 element

    while(true){ // if attempt doesn't work, this loop updates k and retry, until k > 9
      if(k > 9){
        board[i][j] = 0;
        return false;
      }
      board[i][j] = k; // attempt: put k into the element and start to test

      // debug
      // cout<<"\n\n\n\n\n\n\n";
      // void print_board(int[][BOARD_SIZE]);
      // print_board(board);
      // cout<<"i = "<<i<<", j = "<<j<<endl;
      // debug end

      // newest attempt
      if(check_element_condition(board, i, j)){
        if(solve(board, i, j)){
          return true;
        }
      }
      k++;
      continue;
    }
  }
}

bool solve_sudoku(int board[][BOARD_SIZE]){
    return solve(board, 0, 0);
}

void fill_board(int board[][BOARD_SIZE], const char s[]){
    int len = BOARD_SIZE * BOARD_SIZE;
    for(int i = 0; i < len; ++i)
        board[i / BOARD_SIZE][i % BOARD_SIZE] = (int)(s[i] - '0');
}

void print_board(int board[][BOARD_SIZE]){
    cout << "Sudoku board" << endl;
    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j)
            cout << (j ? " " : "") << board[i][j];
        cout << endl;
    }
}

void pause(int dur){
  int temp = time(NULL) + dur;
  while(temp > time(NULL));
}




int main(){
  cout<<"Play sudoku!\n\n\n"<<endl;
  cout<<"Input your board, with \'0\' as empty slots"<<endl;
  char inputBoard[BOARD_SIZE*BOARD_SIZE+1];
   int inputBoardArray[BOARD_SIZE][BOARD_SIZE] ;
  cin.getline(inputBoard, BOARD_SIZE*BOARD_SIZE+1, '\n');
  fill_board(inputBoardArray, inputBoard);
  pause(1); cout<<"Loading ."<<endl; pause(1); cout<<"."<<endl; pause(1); cout<<"."<<endl;pause(1); cout<<"."<<endl;

  print_board(inputBoardArray);
  cout<<"solve it? type yes or no\n\n\n\n"<<endl;
  char permission = 'a';
  cin>>permission;
  if(permission == 'y'){
    if(solve_sudoku(inputBoardArray)){
      cout<<"Solution found!"<<endl;
      print_board(inputBoardArray);
    }
  }
  return 0;
}
