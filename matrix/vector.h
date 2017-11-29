#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

using namespace std;

class Vector{
private:
  int dimension;
  double* vector;

public:
  Vector();
  Vector(int dimension);
  ~Vector();
  int get_dimension();
  double get_element(int num_row); // return element value
  double* get_vector();
  void set_dimension(int dimension);
  void set_element(int num_row, double value);
  void print();
  void initialize_vector();
  void scaling(double scaler = 1); // scale the vector by the scaler
  void dot(Vector* vector);
  void copy(double* vector, int dimension);
};

Vector* dot(Vector* vector_a, Vector* vector_b);
Vector* copy_v(double* vector, int dimension);
#endif
