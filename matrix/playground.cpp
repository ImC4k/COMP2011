#include <iostream>

using namespace std;

const int SIZE = 5;
const int SIZE_2 = 5;
const int SIZE_3 = 5;

enum sign{NEGATIVE = -1, POSITIVE = 1};


void print_matrix(const double matrix[][SIZE], int size = SIZE){
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

double matrix_determinant(double matrix[][SIZE], int size, sign& s, double& scaler){
  // cout<<"function is run, size is "<<size<<endl;
  // print_matrix(matrix, size);
  if(size == 1){
    return (matrix[0][0])*scaler*((s == POSITIVE)? 1 : -1);
  }
  else{
    if(matrix[size - 1][size - 1] != 0){
      // cout<<"row_scaling required"<<endl;
      scaler *=matrix[size - 1][size - 1];
      row_scaling(matrix, size - 1, 1.0/matrix[size - 1][size - 1]);
      // print_matrix(matrix, size);
    }
    else{
      // cout<<"row_interchange required"<<endl;
      int i = 0;
      for(; i < size - 1; i++){
        if(matrix[i][size - 1] != 0){
          break;
        }
      }
      row_interchange(matrix, i, size - 1);
      (s == POSITIVE)? s = NEGATIVE : s = POSITIVE; // change sign after row_interchange
      // cout<<"sign is "<<s<<endl;
      // print_matrix(matrix, size);
      if(matrix[size - 1][size - 1] != 1){
        // cout<<"row_scaling required"<<endl;
        scaler *=matrix[size - 1][size - 1];
        row_scaling(matrix, size - 1, (1.0/matrix[size - 1][size - 1]));
        // print_matrix(matrix, size);
      }
    }
    // cout<<"row_replacement commencing"<<endl;
    for(int j = 0; j < size - 1; j++){
      if(matrix[j][size - 1] != 0){
        row_replacement(matrix, j, size - 1, -1.0*matrix[j][size - 1]);
      }
    }
    // print_matrix(matrix, size);
    return matrix_determinant(matrix, size - 1, s, scaler);
  }
}

void copy_matrix(double matrix_scr[SIZE][SIZE_2], double matrix_des[SIZE][SIZE_2]){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      matrix_des[i][j] = matrix_scr[i][j];
    }
  }
}

void set_identity(double matrix[][SIZE]){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      if( i == j){
        matrix[i][j] = 1;
      }
      else matrix[i][j] = 0;
    }
  }
}

void get_inverse(double matrix_a[SIZE][SIZE], double matrix_b[SIZE][SIZE]){
  double matrixForDeterminant[SIZE][SIZE] = {};
  copy_matrix(matrix_a, matrixForDeterminant);
  sign s = POSITIVE;
  double scaler = 1;
  double determinant = matrix_determinant(matrixForDeterminant, SIZE, s, scaler);
  if( determinant == 0){
    cout<<"There is a singular matrix"<<endl;
    return;
  }
  // cout<<"Determinant of matrix is "<<determinant<<endl<<endl;
  for(int j = 0; j < SIZE; j++){
    if(matrix_a[j][j] == 0){
      int i = j;
      for(; i < SIZE; i++){
        if(matrix_a[i][j] != 0){
          break;
        }
      }
      row_interchange(matrix_a, j, i);
      // cout<<"rows "<<j<<" and "<<i<<" are interchanged"<<endl;
      // print_matrix(matrix_a, SIZE);
      row_interchange(matrix_b, j, i);
    }
    double scaler = 1/matrix_a[j][j];
    if(scaler != 1){
      row_scaling(matrix_a, j, scaler);
      // cout<<"row "<<j<<" is scaled by "<<scaler<<endl;
      // print_matrix(matrix_a, SIZE);
      row_scaling(matrix_b, j, scaler);
    }
    for(int i = 0; i < SIZE; i++){ // row_replacement to create RREF
      if(i == j || matrix_a[i][j] == 0) continue;
      double scaler = -1.0*matrix_a[i][j];
      row_replacement(matrix_a, i, j, scaler);
      // cout<<"row "<<j<<"* "<<scaler<<" added to row "<<i<<endl;
      // print_matrix(matrix_a, SIZE);
      row_replacement(matrix_b, i, j, scaler);
    }
  }
}

void multiply_matrix(double matrix_a[SIZE][SIZE_2], double matrix_b[SIZE_2][SIZE_3], double output[SIZE][SIZE_3]){
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE_3; j++)
      output[i][j] = 0;
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE_2; j++){
      for(int k = 0; k < SIZE_3; k++){
        output[i][k] += matrix_a[i][j]*matrix_b[j][k];
      }
    }
  }
}

void multiply_inverse(double matrix_a[SIZE][SIZE_2], double matrix_b[SIZE_2][SIZE_3]){
  double output[SIZE][SIZE_3] = {};
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE_2; j++){
      for(int k = 0; k < SIZE_3; k++){
        output[i][k] += matrix_a[i][j]*matrix_b[j][k];
      }
    }
  }
  cout<<"product is "<<endl;
  print_matrix(output);
}

int main(){
  // double matrix[][SIZE] = {{3, 0, 0, 2, 0},
  //                       {1, 0, -3, 0, 0},
  //                       {0, 1, 0, 0, 3},
  //                       {0, 0, 0, 1, 2},
  //                       {0, 3, 1, 0, 0}};

  // double matrix[][SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // double matrix[][SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
  double matrix[][SIZE] = {1, 2, 0, 0, 0, 2, 1, 2, 0, 0, 0, 2, 1, 2, 0, 0, 0, 2, 1, 2, 0, 0, 0, 2, 1};
  // double matrix_a[SIZE][SIZE_2] = {{8, 6, 3}, {4, 4, 4},{ 1, 2, 3}};
  double matrix_b[SIZE][SIZE] = {};
  double product_ab[SIZE][SIZE] = {};
  double matrixForInverse[SIZE][SIZE_2] = {};
  sign s = POSITIVE;
  double scaler = 1;
  cout<<matrix_determinant(matrix, SIZE, s, scaler)<<endl;
  // copy_matrix(matrix_a, matrixForInverse);
  // set_identity(matrix_b);
  // set_identity(product_ab);
  // get_inverse(matrixForInverse, matrix_b);
  // print_matrix(matrix_a, SIZE);
  // cout<<"\n\n\n\n\n";
  // cout<<"inverse is "<<endl;
  // print_matrix(matrix_b);

  // multiply_matrix(matrix_a, matrix_b);
  // multiply_matrix(matrix_a, matrix_b, product_ab);
  //
  // cout<<"when matrix_a \n";
  // print_matrix(matrix_a);
  // cout<<" and matrix_b \n";
  // print_matrix(matrix_b);
  // cout<<" multiply, we get \n";
  // print_matrix(product_ab);

  // sign s = POSITIVE;
  // double scaler = 1;
  // double determinant = matrix_determinant(matrix, SIZE, s, scaler);
  // cout<<((s == POSITIVE)? 1 : -1)*scaler<<endl;
  // cout<<"determinant is "<<determinant<<endl;


  return 0;
}
