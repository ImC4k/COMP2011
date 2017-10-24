#include <iostream>
// #include "matrix_global.h"

using namespace std;

// extern int SIZE;
const int SIZE = 3;

int get_matrix_size();
void print_matrix(int[][SIZE]);
void row_scaling(int[][SIZE], const int, const int);
void row_interchange(int[][SIZE], const int, const int);
void row_replacement(int[][SIZE], const int, const int, const int);
int determinent(int[][SIZE]);


// int get_matrix_size(){
//   cout<<"Please enter size of matrix operation: "<<endl; // get the SIZE of matrix operation
//   while(true){
//     cin>> SIZE;
//     if(static_cast<int>(SIZE) > 0){
//       break;
//     }
//     cout<<"Invalid input, size should be larger than 0"<<endl;
//   }
//   return SIZE;
// }

void print_matrix(int matrix[][SIZE]){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      cout<<matrix[i][j];
      if(j != SIZE - 1){
        cout<<' ';
      }
    }
    cout<<endl;
  }
}



void row_scaling(int matrix[][SIZE], const int num_row, const int scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[num_row - 1][i] *= scaler;
  }
}

void row_interchange(int matrix[][SIZE], const int num_row_1, const int num_row_2){
  for(int i = 0; i < SIZE; i++){
    int temp = matrix[num_row_1 - 1][i];
    matrix[num_row_1 - 1][i] = matrix[num_row_2 - 1][i];
    matrix[num_row_2 - 1][i] = temp;
  }
}

void row_replacement(int matrix[][SIZE], const int target_row, const int add_row, const int scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[target_row - 1][i] += matrix[add_row - 1][i]*scaler;
  }
}

int determinent(int matrix[][SIZE]){
  int determinent = 0;
  for(int i = 0; i < 3; i++){
    int diagonal_product_p = 1;
    for(int j = 0; j < 3; j++){
      diagonal_product_p *= matrix[(i+j)%SIZE][j];
    }
    determinent += diagonal_product_p;
  }
  for(int i = 0; i < 3; i++){
    int diagonal_product_n = 1;
    for(int j = 0; j < 3; j++){
      diagonal_product_n *= matrix[(i-j+2)%SIZE][j];
    }
    determinent -= diagonal_product_n;
  }

  return determinent;
}
