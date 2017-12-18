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
  Matrix();
  Matrix(int num_row, int num_col);
  ~Matrix();
  bool initialize_matrix(); // initialize_matrix pointers, and set all elements to 0

  int get_num_row();
  int get_num_col();
  double get_determinant();
  double** get_matrix();
  double get_element(int num_row, int num_col);
  void set_num_row(int num_row);
  void set_num_col(int num_col);
  void set_element(int num_row, int num_col, double value);
  void set_matrix(double** matrix);

  void input_elements(); // allows users to input every element on console
  void add(const Matrix* src); // add two matrix together
  void print();
  void row_scaling(const int num_row, const double scaler);
  void row_interchange(const int num_row_1, const int num_col_2); // swap num_row_1 and num_row_2
  void row_replacement(const int target_row, const int add_row, const double scaler); //
  void multiply_scaler(const double scaler);
  void copy(double** matrix, int matrix_row, int matrix_col);
  void reset(int option = 1); // options: 0: all 0, 1: identity, 2: all 1
  void update_determinant();
  // span
  // gram_schmidt process
  };

Matrix* copy_m(double** matrix, int matrix_row, int matrix_col);
Matrix* multiply_matrix_m(Matrix* matrix_left, Matrix* matrix_right);
Matrix* inverse(Matrix* src); // put the inverse of src to another matrix object (square matrix)
Matrix* transpose(Matrix* src); // get the transpose of a matrix
// TODO functions: eigen values
// TODO functions: orthonormal matrix

#endif
