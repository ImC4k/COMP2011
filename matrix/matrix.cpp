#include "matrix.h"

Matrix::Matrix(){
    num_row = 0;
    num_col = 0;
    determinant = 0;
    matrix = nullptr;
}

Matrix::Matrix(int num_row, int num_col){
  this->num_row = num_row;
  this->num_col = num_col;
  determinant = 0;
  initialize_matrix();
  reset(0);
}

Matrix::~Matrix(){
  for(int i = 0; i < num_row; i++){
    delete[] matrix[i];
  }
  delete[] matrix;
  matrix = nullptr;
}

bool Matrix::initialize_matrix(){
  if(num_row == 0 || num_col == 0){
    cout<<"matrix dimension not defined properly"<<endl;
    return false;
  }

  matrix = new double* [num_row];
  for(int i = 0; i < num_row; i++){
    matrix[i] = new double [num_col];
  }
  reset(0);
  return true;
}

int Matrix::get_num_row(){
  return num_row;
}

int Matrix::get_num_col(){
  return num_col;
}

double Matrix::get_determinant(){
  // update_determinant();
  return determinant;
}

double** Matrix::get_matrix(){
  return matrix;
}

double Matrix::get_element(int num_row, int num_col){
  return matrix[num_row][num_col];
}

void Matrix::set_num_row(int num_row){
  this->num_row = num_row;
}

void Matrix::set_num_col(int num_col){
  this->num_col = num_col;
}

void Matrix::set_element(int num_row, int num_col, double value){
  matrix[num_row][num_col] = value;
  // update_determinant();
}

void Matrix::set_matrix(double** matrix){
  this->matrix = matrix;
  // update_determinant();
}

void Matrix::input_elements(){ // allows users to input every element on console
  if(num_row == 0 || num_col == 0){
    cout<<"Matrix not initialized properly"<<endl;
    return;
  }
  cout<<"Please input values for your matrix: "<<endl;
  for(int i = 0; i < num_row; i++){
    for(int j = 0; j < num_col; j++){
      cin>>matrix[i][j];
    }
  }
}

void Matrix::add(const Matrix* src){
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

void Matrix::print(){
  cout<<endl;
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

double Matrix::calc_determinant(){
  if(num_row != num_col){
    cout<<"matrix is not square, cannot compute determinant"<<endl;
    return -1;
  }
  int size = num_row;
  double scaler = 1;
  Matrix* temp_matrix = copy_m(matrix, num_row, num_col);
  double determinant = determinant_r(temp_matrix, size, scaler);
  delete temp_matrix;

  return determinant;
}

double Matrix::determinant_r(Matrix* src, int size, double& scaler){
  if(size == 1){
    return (src->matrix[0][0])*scaler;
  }
  else{
    if(src->matrix[size - 1][size - 1] != 0){ // right-bottom is not 0
      scaler *=src->matrix[size - 1][size - 1];
      src->row_scaling(size - 1, 1.0/src->matrix[size - 1][size - 1]);
    }
    else{ // right-bottom is 0
      int i = 0;
      bool found_non_zero_row = false;
      for(; i < size - 1; i++){
        if(src->matrix[i][size - 1] != 0){
          found_non_zero_row = true;
          break;
        }
      }
      if(!found_non_zero_row){
        return 0;
      }
      src->row_interchange(i, size - 1);
      scaler *= -1; // change sign after row_interchange
      if(src->matrix[size - 1][size - 1] != 1){
        scaler *= src->matrix[size - 1][size - 1];
        src->row_scaling(size - 1, (1.0/src->matrix[size - 1][size - 1]));
      }
    }
    for(int j = 0; j < size - 1; j++){
      if(src->matrix[j][size - 1] != 0){
        src->row_replacement(j, size - 1, -1.0*src->matrix[j][size - 1]);
      }
    }
    return determinant_r(src, size - 1, scaler);
  }
}

void Matrix::copy(double** matrix, int num_row, int num_col){
  if(this->num_row != num_row || this->num_col != num_col){
    cout<<"different dimension matrix object, cannot copy"<<endl;
    return;
  }
  for(int i = 0; i < num_row; i++){
    for(int j = 0; j < num_col; j++){
      this->matrix[i][j] = matrix[i][j];
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
    determinant = 0;
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
    determinant = 1;
    break;

    case 2:
    for(int i = 0; i < num_row; i++){
      for(int j = 0; j < num_col; j++){
        matrix[i][j] = 1;
      }
    }
    determinant = 0;
    break;

    default: return;
  }
  return;
}

void Matrix::update_determinant(){
  determinant = calc_determinant();
}









Matrix* copy_m(double** matrix, int num_row, int num_col){
  Matrix* result = new Matrix(num_row, num_col);
  result->copy(matrix, num_row, num_col);
  return result;
}

Matrix* multiply_matrix_m(Matrix* a, Matrix* b){
  if(a->get_num_col() != b->get_num_row()){
    cout<<"matrix dimension does not match, cannot multiply"<<endl;
    return nullptr;
  }

  Matrix* result = new Matrix();
  int num_row = a->get_num_row();
  int num_col = b->get_num_col();
  result->set_num_row(num_row);
  result->set_num_col(num_col);

  result->initialize_matrix();
  double** matrix = result->get_matrix();
  for(int i = 0; i < num_row; i++){ // real multiply part
    for(int j = 0; j < a->get_num_col(); j++){
      for(int k = 0; k < num_col; k++){
        matrix[i][k] += a->get_element(i, j)*b->get_element(j, k);
      }
    }
  }
  return result;
}

Matrix* inverse(Matrix* src){
  if(src->get_determinant() == 0){ // also checked if it's a square matrix
    cout<<"That matrix has no inverse"<<endl;
    return nullptr;
  }
  Matrix* src_copy = new Matrix();
  src_copy->set_num_row(src->get_num_row());
  src_copy->set_num_col(src->get_num_col());
  src_copy->initialize_matrix();
  src_copy->copy(src->get_matrix(), src->get_num_row(), src->get_num_col()); // save a copy for manipulation
  Matrix* result = new Matrix(src_copy->get_num_row(), src_copy->get_num_col()); // all set to 0;
  result->reset(1); // set to identity

  for(int j = 0; j < src_copy->get_num_col(); j++){
    if(src_copy->get_element(j, j) == 0){ // check if diagonal element is 0
      int i = j;
      for(; i < src_copy->get_num_row(); i++){
        if(src_copy->get_element(i, j) != 0){
          break;
        }
      }
      src_copy->row_interchange(j, i);
      result->row_interchange(j, i);
    }
    double scaler = 1/src_copy->get_element(j, j);
    if(scaler != 1){
      src_copy->row_scaling(j, scaler);
      result->row_scaling(j, scaler);
    }
    for(int i = 0; i < src->get_num_row(); i++){ // row_replacement to create RREF
      if(i == j || src_copy->get_element(i,j) == 0) continue;
      double scaler = -1.0*src_copy->get_element(i,j);
      src_copy->row_replacement(i, j, scaler);
      result->row_replacement(i, j, scaler);
    }
  }

  delete src_copy;
  return result;
}

Matrix* transpose(Matrix* src){
  Matrix* result = new Matrix(src->get_num_col(), src->get_num_row());
  result->initialize_matrix();
  for(int i = 0; i < result->get_num_row(); i++){
    for(int j = 0; j < result->get_num_col(); j++){
      result->set_element(i, j, src->get_element(j, i));
    }
  }
  return result;
}
