#ifndef VECTOR_H_
#define VECTOR_H_

#include "utils.h"


class Vector{
private:
  int dimension; // num_row
  double* vector; // double array for data

public:
  Vector();
  Vector(int dimension);
  ~Vector();
  int get_dimension();
  double get_element(int num_row); // return element value
  double* get_vector();
  void set_dimension(int dimension);
  void set_element(int num_row, double value);
  void set_vector(double* vector);
  void input_elements(); // for user to input using console
  void print();
  void initialize_vector();
  void scaling(double scaler = 1); // scale the vector by the scaler
  void add(Vector* src);
  void subtract(Vector* src);
  double dot(Vector* vector);
  void copy(double* vector, int dimension);
  void copy(Vector* vector); // overloaded function
  void expand_dimension(int dimension);
};

double dot(Vector* vector_a, Vector* vector_b);
Vector* add(Vector* vector_a, Vector* vector_b); // return a new vector, element is sum of two vectors
Vector* subtract(Vector* vector_a, Vector* vector_b);
Vector* copy_v(double* vector, int dimension);
Vector* copy_v(Vector* vector);
Vector* expand_dimension(Vector* vector, int dimension);

Vector* create(double* vector, int dimension);
Vector* convert(double* vector_arr, int dimension); // convert an array to a vector
#endif
