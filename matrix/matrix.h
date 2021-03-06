#ifndef MATRIX_H_
#define MATRIX_H_

#include "utils.h"
#include "vector.h"

class Matrix{
private:
  int num_row;
  int num_col;
  double determinant;
  double** matrix;

  double determinant_r(Matrix* matrix, int size, double& scaler);
  double calc_determinant(); // when called, must supply sign and scaler variable

public:
  Matrix(); // all propeties are initialized as 0 or nullptr
  Matrix(int num_row, int num_col); // initialize num_row and num_col, matrix data strage is also reserved by dynamic array
  ~Matrix(); // will delete matrix property
  bool initialize_matrix(); // initialize_matrix pointers based on num_row and num_col, and set all elements to 0

  int get_num_row();
  int get_num_col();
  double get_determinant();
  double** get_matrix(); // returns all matrix data as 2d dynamic array
  double get_element(int num_row, int num_col);
  void set_num_row(int num_row);
  void set_num_col(int num_col);
  void set_element(int num_row, int num_col, double value);
  void set_column(Vector* vector, int num_col);
  //BUG set_matrix() needs further investigation
  void set_matrix(double** matrix); // deletes original dynamic array, and points to parsed "matrix" dynamic array
  void input_elements(); // allows users to input every element on console

  void add(const Matrix* src); // add two matrix together
  void subtract(const Matrix* src);
  void print();


  void row_scaling(const int num_row, const double scaler);
  void row_interchange(const int num_row_1, const int num_col_2); // swap num_row_1 and num_row_2
  void row_replacement(const int target_row, const int add_row, const double scaler); //eg target = target + scaler*add
  void multiply_scaler(const double scaler); // multiply a scaler to entire matrix
  void copy(double** matrix, int matrix_row, int matrix_col);
  void reset(int option = 1); // options: 0: all 0, 1: identity, 2: all 1
  void update_determinant();
  // span
  };

Matrix* copy_m(double** matrix, int matrix_row, int matrix_col);
Matrix* copy_m(Matrix* src);
Matrix* multiply_matrix_m(Matrix* matrix_left, Matrix* matrix_right);
Matrix* inverse(Matrix* src); // put the inverse of src to another matrix object (square matrix)
Matrix* transpose(Matrix* src); // get the transpose of a matrix

#endif
