#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

using namespace std;

enum sign{NEGATIVE = -1, POSITIVE = 1};

class Matrix{
private:
  int num_row;
  int num_col;
  double** matrix;
  double determinant_r(sign&, double& scaler);

public:
  Matrix(int num_row, int num_col);
  ~Matrix();
  void add(const Matrix src); // add two matrix together
  void print_matrix();
  void row_scaling(const int num_row, const double scaler);
  void row_interchange(const int num_row_1, const int num_col_2);
  void row_replacement(const int target_row, const int add_row, const double scaler);
  void multiply_scaler(const double scaler);
  double determinant(); // when called, must supply sign and scaler variable
  void copy_matrix(const Matrix src);
  void reset(int option = 1); // options: 0: all zero, 1: identity
  Matrix* multiply_matrix(const Matrix src);
  Matrix* get_inverse(const Matrix src); // put the inverse of src to another matrix object
};

#endif
