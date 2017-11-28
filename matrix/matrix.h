#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

using namespace std;

enum sign{NEGATIVE = -1, POSITIVE = 1};

class Matrix{
private:
  int num_row;
  int num_col;
  double determinant;
  double** matrix;

  double determinant_r(sign&, double& scaler);
  double determinant() const; // when called, must supply sign and scaler variable

public:
  Matrix();
  Matrix(int num_row, int num_col);
  ~Matrix();
  bool initialize_matrix(); // initialize_matrix pointers, and set all elements to 0
  double get_num_row();
  double get_num_col();
  double get_determinant();
  double** get_matrix();
  double get_element(int num_row, int num_col);
  void set_num_row(int num_row);
  void set_num_col(int num_col);
  // void set_determinant(double determinant);
  void set_element(int num_row, int num_col, double value);
  void set_matrix(double** matrix);
  void input_elements(); // allows users to input every element on console
  void add(const Matrix src); // add two matrix together
  void print_matrix();
  void row_scaling(const int num_row, const double scaler);
  void row_interchange(const int num_row_1, const int num_col_2);
  void row_replacement(const int target_row, const int add_row, const double scaler);
  void multiply_scaler(const double scaler);
  void copy_matrix(const Matrix src);
  void reset(int option = 1); // options: 0: all zero, 1: identity
  void update_determinant();
  };

Matrix* copy_matrix(const Matrix src);
Matrix* multiply_matrix(const Matrix src);
Matrix* inverse(const Matrix src); // put the inverse of src to another matrix object (square matrix)
Matrix* transpose(const Matrix src); // get the transpose of a matrix


#endif
