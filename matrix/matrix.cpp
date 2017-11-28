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
}

bool initialize_matrix(){
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

double Matrix::get_num_row(){
  return num_row;
}

double Matrix::get_num_col(){
  return num_col;
}

double Matrix::get_determinant(){
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

// void Matrix::set_determinant(double determinant){
//   this->determinant = determinant;
// }

void set_element(int num_row, int num_col, double value){
  matrix[num_row][num_col] = value;
}

void Matrix::set_matrix(double** matrix){
  this->matrix = matrix;
}

void Matrix::input_elements(){ // allows users to input every element on console
  //TODO
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

double Matrix::determinant() const{
  if(num_row != num_col){
    cout<<"matrix is not square, cannot compute determinant"<<endl;
    return -1;
  }
  int size = num_row;
  sign s = POSITIVE;
  double scaler = 1;
  Matrix* temp_matrix = copy_matrix(this->matrix);
  double determinant = determinant_r(temp_matrix, size, s, scaler);
  delete temp_matrix;

  return determinant;
}

double Matrix::determinant_r(Matrix* matrix, int size, sign& s, double& scaler){
  // TODO
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
    return determinant_r(matrix, size - 1, s, scaler);
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

void Matrix::update_determinant(){
  determinant = determinant();
}








Matrix* copy_matrix(const Matrix src){
  Matrix* result = new Matrix();
  int num_row = src->get_num_row();
  int num_col = src->get_num_col();
  result->set_num_row(num_row);
  result->set_num_col(num_col);
  result->initialize_matrix();
  result->copy_matrix(src);
  return result;
}

Matrix* multiply_matrix(const Matrix a, const Matrix b){
  if(a->get_num_col() != b->get_num_row()){
    cout<<"matrix dimension does not match, cannot multiply"<<endl;
    return nullptr;
  }
  Matrix* result = new Matrix();
  int num_row = a->get_num_row();
  int num_col = b->get_num_col();
  result->set_num_row(num_row);
  reselt->set_num_col(num_col);

  result->initialize_matrix();
  double** matrix = result->get_matrix();
  for(int i = 0; i < num_row; i++){ // real multiply part
    for(int j = 0; j < num_col; j++){
      for(int k = 0; k < a->get_num_col()){
        matrix[i][k] += a->get_element(i, j)*b->get_element(j, k);
      }
    }
  }
  return result;
}

Matrix* inverse(const Matrix src){
  // TODO
  if(src->get_determinant() == 0){
    cout<<"That matrix has no inverse"<<endl;
    return nullptr;
  }
  Matrix* src_copy = new Matrix();
  int num_row = src->get_num_row();
  int num_col = src->get_num_col();
  src_copy->initialize_matrix();
  src_copy->set_num_row(num_row);
  src_copy->set_num_col(num_col);
  src_copy->copy_matrix(src); // save a copy for manipulation

  Matrix* result = new Matrix();
  result->reset(); // result matrix is set to identity


  delete src_copy;
  return result;
}

Matrix* transpose(const Matrix src){
  Matrix* result = new Matrix(src->get_num_col(), src->get_num_row());
  result->initialize_matrix();
  for(int i = 0; i < result->get_num_row(); i++){
    for(int j = 0; j < result->get_num_col(); j++){
      result->set_element(i, j, src->get_element(j, i));
    }
  }
  return result;
}
