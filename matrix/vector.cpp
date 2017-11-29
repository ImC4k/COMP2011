#include "vector.h"

Vector::Vector(){
  dimension = 0;
  vector = nullptr;
}

Vector::Vector(int dimension){
  this->dimension = dimension;
  initialize_vector();
}

Vector::~Vector(){
  delete[] vector;
  vector = nullptr;
}

int Vector::get_dimension(){
  return dimension;
}

double Vector::get_element(int num_row){
  return vector[num_row];
}

double* Vector::get_vector(){
  return vector;
}

void Vector::set_dimension(int dimension){
  this->dimension = dimension;
}

void Vector::set_element(int num_row, double value){
  vector[num_row] = value;
}

void Vector::print(){
  cout<<endl;
  for(int i = 0; i < dimension; i++){
    cout<<vector[i]<<endl;
  }
  cout<<endl;
}

void Vector::initialize_vector(){
  vector = new double [dimension];
  scaling(0);
}

void Vector::scaling(double scaler){
  if(dimension == 0){
    cout<<"vector dimension not initialized properly"<<endl;
    return;
  }
  for(int i = 0; i < dimension; i++){
    vector[i] = scaler;
  }
}

void Vector::dot(Vector* src){
  if(this->dimension != src->dimension){
    cout<<"mismatch of dimension"<<endl;
    return;
  }
  for(int i = 0; i < this->dimension; i++){
    this->vector[i] *= src->vector[i];
  }
}

void Vector::copy(double* vector, int dimension){
  if(this->dimension != dimension){
    cout<<"mismatch dimension"<<endl;
    return;
  }
  for(int i = 0; i < dimension; i++){
    this->vector[i] = vector[i];
  }
}




Vector* dot(Vector* vector_a, Vector* vector_b){
  if(vector_a->get_dimension() != vector_b->get_dimension()){
    cout<<"mismatch of dimension"<<endl;
    return nullptr;
  }
  Vector* result = new Vector(vector_a->get_dimension());
  for(int i = 0; i < result->get_dimension(); i++){
    double value = vector_a->get_element(i) * vector_b->get_element(i);
    result->set_element(i, value);
  }
  return result;
}

Vector* copy_v(double* vector, int dimension){
  Vector* result = new Vector(dimension);
  result->copy(vector, dimension);
  return result;
}
