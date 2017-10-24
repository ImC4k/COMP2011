#include <iostream>

using namespace std;

const int SIZE = 5;

enum sign{NEGATIVE = -1, POSITIVE = 1};


void print_matrix(double matrix[][SIZE], int size){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      cout<<matrix[i][j];
      if(j != size - 1){
        cout<<' ';
      }
    }
    cout<<endl;
  }
}

void row_scaling(double matrix[][SIZE], const int num_row, const double scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[num_row][i] *= scaler;
  }
}

void row_interchange(double matrix[][SIZE], const int num_row_1, const int num_row_2){
  for(int i = 0; i < SIZE; i++){
    int temp = matrix[num_row_1][i];
    matrix[num_row_1][i] = matrix[num_row_2][i];
    matrix[num_row_2][i] = temp;
  }
}

void row_replacement(double matrix[][SIZE], const int target_row, const int add_row, const double scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[target_row][i] += matrix[add_row][i]*scaler;
  }
}

double determinent_3(double matrix[][SIZE]){
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

double matrix_determinent(double matrix[][SIZE], int size, sign s, double scaler){
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


int main(){
  double matrix[][SIZE] = {{3, 0, 0, 2, 0},
                        {1, 0, -3, 0, 0},
                        {0, 1, 0, 0, 3},
                        {0, 0, 0, 1, 2},
                        {0, 3, 1, 0, 0}};
  sign s = POSITIVE;
  int scaler = 1;
  double determinent = matrix_determinent(matrix, SIZE, s, scaler);
  cout<<determinent<<endl;
  return 0;
}
