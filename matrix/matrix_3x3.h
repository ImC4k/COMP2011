#include <iostream>
// #include "matrix_global.h"

using namespace std;

// extern int SIZE;
const int SIZE;

int get_matrix_size();
void print_matrix(double[][SIZE]);
void row_scaling(double[][SIZE], const int, const double);
void row_interchange(double[][SIZE], const int, const int);
void row_replacement(double[][SIZE], const int, const int, const double);
double determinent(double[][SIZE]);


int get_matrix_size(int &input_size){
  SIZE = &input_size;
  cout<<"Please enter size of matrix operation: "<<endl; // get the SIZE of matrix operation
  while(true){
    cin>> input_size;
    if(static_cast<int>(input_size) > 0){
      break;
    }
    cout<<"Invalid input, size should be larger than 0"<<endl;
  }
  return input_size;
}

void print_matrix(double matrix[][SIZE]){
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



void row_scaling(double matrix[][SIZE], const int num_row, const double scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[num_row - 1][i] *= scaler;
  }
}

void row_interchange(double matrix[][SIZE], const int num_row_1, const int num_row_2){
  for(int i = 0; i < SIZE; i++){
    int temp = matrix[num_row_1 - 1][i];
    matrix[num_row_1 - 1][i] = matrix[num_row_2 - 1][i];
    matrix[num_row_2 - 1][i] = temp;
  }
}

void row_replacement(double matrix[][SIZE], const int target_row, const int add_row, const double scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[target_row - 1][i] += matrix[add_row - 1][i]*scaler;
  }
}

double matrix_determinent(double matrix[][SIZE], int size, sign& s, double& scaler){
  cout<<"function is run, size is "<<size<<endl;
  print_matrix(matrix, size);
  if(size == 2){
    return (matrix[0][0]*matrix[1][1]-matrix[1][0]*matrix[0][1])*scaler*((s == POSITIVE)? 1 : -1);
  }
  else{
    if(matrix[size - 1][size - 1] != 0){
      cout<<"row_scaling required"<<endl;
      scaler *=matrix[size - 1][size - 1];
      row_scaling(matrix, size - 1, 1.0/matrix[size - 1][size - 1]);
      print_matrix(matrix, size);
    }
    else{
      cout<<"row_interchange required"<<endl;
      int i = 0;
      for(; i < size - 1; i++){
        if(matrix[i][size - 1] != 0){
          break;
        }
      }
      row_interchange(matrix, i, size - 1);
      (s == POSITIVE)? s = NEGATIVE : s = POSITIVE; // change sign after row_interchange
      cout<<"sign is "<<s<<endl;
      print_matrix(matrix, size);
      if(matrix[size - 1][size - 1] != 1){
        cout<<"row_scaling required"<<endl;
        scaler *=matrix[size - 1][size - 1];
        row_scaling(matrix, size - 1, static_cast<double>(1.0/matrix[size - 1][size - 1]));
        print_matrix(matrix, size);
      }
    }
    cout<<"row_replacement commencing"<<endl;
    for(int j = 0; j < size - 1; j++){
      if(matrix[j][size - 1] != 0){
        row_replacement(matrix, j, size - 1, -1.0*matrix[j][size - 1]);
      }
    }
    print_matrix(matrix, size);
    return matrix_determinent(matrix, size - 1, s, scaler);
  }
}
