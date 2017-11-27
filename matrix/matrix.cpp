#include "matrix.h"

Matrix::Matrix(int num_row, int num_col){
  this->num_row = num_row;
  this->num_col = num_col;
  matrix = new* double[num_row];
  for(int i = 0; i < num_row; i++){
    matrix[i] = new double[num_col];
    for(int j = 0; j << num_col; j++){
      matrix[i][j] = NULL;
    }
  }
}

Matrix::~Matrix(){
  for(int i = 0; i < num_row; i++){
    delete[] matrix[i];
  }
  delete[] matrix;
}

void Matrix::add(const Matrix src){
  if(src->num_row != this->num_row || src->num_col != this->num_col){
    cout<<"Incompatible dimension, matrix cannot be added"<<endl;
    return;
  }
  for(int i = 0; i < num_row; i++){
    for(int j = 0; j < num_col; j++){
      matrix[i][j] += src->matrix[i][j];
    }
  }
}

void Matrix::print_matrix(){
  for(int i = 0; i < num_row; i++){
    for(int j = 0; j < num_col; j++){
      cout<<matrix[i][j]<<"\t";
    }
    cout<<endl;
  }
}

void Matrix::row_scaling(const int num_row, const double scaler){
  if(num_row >= this->num_row || num_row < 0){
    cout<<"row number is invalid"<<endl;
    return;
  }
  for(int i = 0; i < num_col; i++){
    matrix[num_row][i] *= scaler;
  }
}

void Matrix::row_interchange(const int num_row_1, const int num_row_2){
  if(num_row_1 >= this->num_row || num_row_1 < 0 || num_row_2 >= this->num_row || num_row_2 < 0){
    cout<<"row number is invalid"<<endl;
    return;
  }
  double* temp_row_ptr = matrix[num_row_1];
  matrix[num_row_1] = matrix[num_row_2];
  matrix[num_row_2] = temp_row_ptr;
}

void Matrix::row_replacement(const int target_row, const int add_row, const double scaler){
  if(target_row >= this->num_row || target_row < 0 || add_row >= this->num_row || add_row < 0){
    cout<<"row number is invalid"<<endl;
    return;
  }
  for(int i = 0; i < num_col; i++){
    matrix[target_row][i] += matrix[add_row][i]*scaler;
  }
}

void Matrix::multiply_scaler(const double scaler){
  for(int i = 0; i < num_row; i++){
    row_scaling(i, scaler);
  }
}

double Matrix::determinant(){
  if(num_row != num_col){
    cout<<"matrix is not square, cannot compute determinant"<<endl;
    return -1;
  }
  int size = num_row;
  sign s = POSITIVE;
  double scaler = 1;
  return determinant_r(size, s, scaler);
}

double Matrix::determinant_r(int size, sign& s, double& scaler){
  if(size == 1){
    return (matrix[0][0])*scaler*((s == POSITIVE)? 1 : -1);
  }
  else{
    if(matrix[size - 1][size - 1] != 0){
      scaler *=matrix[size - 1][size - 1];
      row_scaling(matrix, size - 1, 1.0/matrix[size - 1][size - 1]);
    }
    else{
      int i = 0;
      for(; i < size - 1; i++){
        if(matrix[i][size - 1] != 0){
          break;
        }
      }
      row_interchange(matrix, i, size - 1);
      (s == POSITIVE)? s = NEGATIVE : s = POSITIVE; // change sign after row_interchange
      if(matrix[size - 1][size - 1] != 1){
        scaler *=matrix[size - 1][size - 1];
        row_scaling(matrix, size - 1, (1.0/matrix[size - 1][size - 1]));
      }
    }
    for(int j = 0; j < size - 1; j++){
      if(matrix[j][size - 1] != 0){
        row_replacement(matrix, j, size - 1, -1.0*matrix[j][size - 1]);
      }
    }
    return matrix_determinant(matrix, size - 1, s, scaler);
  }
}

void Matrix::copy_matrix(const Matrix src){
  if(num_row != src->num_row || num_col != src->num_col){
    cout<<"different dimension matrix object, cannot copy"<<endl;
    return;
  }
  for(int i = 0; i < num_row; i++){
    for(int j = 0; j < num_col; j++){
      matrix[i][j] = src->matrix[i][j];
    }
  }
}

void Matrix::reset(int option){
  switch(option){
    case 0:
    for(int i = 0; i < num_row; i++){
      for(int j = 0; j < num_col; j++){
        matrix[i][j] = 0;
      }
    }
    break;

    case 1:
    for(int i = 0; i < num_row; i++){
      for(int j = 0; j < num_col; j++){
        matrix[i][j] = 0;
        if(i== j){
          matrix[i][j] = 1;
        }
      }
    }
    break;

    default return;
  }
  return;
}

Matrix* Matrix::multiply_matrix(const Matrix src){

}

Matrix* Matrix::get_inverse(const Matrix src){
  
}
