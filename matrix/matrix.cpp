#include <iostream>
#include "matrix_3x3.h"
// #include "matrix_global.h"

using namespace std;


int main(){
  // SIZE = get_matrix_size();
  int matrix[][3] = {{1, 0, 0},
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
