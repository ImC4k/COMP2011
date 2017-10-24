#include <iostream>
#include "matrix_3x3.h"
// #include "matrix_global.h"

using namespace std;


int input_size = 0;
int SIZE = &input_size;

int main(){

  input_size = get_matrix_size(input_size);
  int matrix[][*SIZE] = {{1, 0, 0},
                            {0, 1, 0},
                            {0, 0, 1}};

  print_matrix(matrix);
  row_interchange(matrix, 1, 3);
  cout<<endl;

  print_matrix(matrix);
  row_scaling(matrix, 2, 3);
  cout<<endl;

  print_matrix(matrix);
  row_replacement(matrix, 1, 2, 1);
  cout<<endl;
  print_matrix(matrix);
  cout<<endl;
  cout<<determinent(matrix)<<endl;
}
