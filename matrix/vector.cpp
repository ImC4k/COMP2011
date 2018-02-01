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

void Vector::set_vector(double* vector){
  this->vector = vector;
}

void Vector::input_elements(){
  cout<<"Please input values for your vector: "<<endl;
  for(int i = 0; i < dimension; i++){
    cin>>vector[i];
  }
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

void Vector::add(Vector* src){
  if(this->dimension != src->dimension){
    cout<<"mismatch of dimension"<<endl;
    return;
  }
  for(int i = 0; i < this->dimension; i++){
    this->vector[i] += src->vector[i];
  }
}

void Vector::subtract(Vector* src){
  if(this->dimension != src->dimension){
    cout<<"mismatch of dimension"<<endl;
    return;
  }
  for(int i = 0; i < this->dimension; i++){
    this->vector[i] -= src->vector[i];
  }
}

double Vector::dot(Vector* src){
  if(this->dimension != src->dimension){
    cout<<"mismatch of dimension"<<endl;
    return;
  }
  double value = 0;
  for(int i = 0; i < this->dimension; i++){
    value += this->get_element(i) * src->get_element(i);
  }
  return value;
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

void Vector::copy(Vector* vector){
  if(this->vector != nullptr) delete[] vector;
  this->dimension = vector->dimension;
  this->vector = new double[this->dimension];
  for(int i = 0; i < this->dimension; i++){
    this->vector[i] = vector->vector[i];
  }
}

/* Non member functions */


double dot(Vector* vector_a, Vector* vector_b){
  if(vector_a->get_dimension() != vector_b->get_dimension()){
    cout<<"mismatch of dimension"<<endl;
    return nullptr;
  }
  double value = 0;
  for(int i = 0; i < vector_a->get_dimension(); i++){
    value += vector_a->get_element(i) * vector_b->get_element();
  }
  return value;
}

Vector* copy_v(double* vector, int dimension){
  Vector* result = new Vector(dimension);
  result->copy(vector, dimension);
  return result;
}

Vector* copy_v(Vector* src){
  Vector* result = new Vector(src->get_dimension());
  result->copy(src->get_vector(), src->get_dimension());
  return result;
}

Vector* expand_dimension(Vector* src, int dimension){
  if(src->get_dimension() > dimension){
    cout<<"original dimension larger than wanted dimension"<<endl;
    return nullptr;
  }
  else if(src->get_dimension() == dimension) return src;
  else{
    Vector* expanded_v = new Vector(dimension);
    double* new_vector = new double[dimension];
    for(int i = 0; i < src->get_dimension(); i++){
      new_vector[i] = src->get_element(i);
    }
    for(int i = src->get_dimension(); i < dimension; i++){
      new_vector[i] = 0;
    }
    expanded_v->set_vector(new_vector);
    return expanded_v;
  }
}

Vector* create(double* vector, int dimension){
  Vector* result = new Vector();
  result->set_dimension(dimension);
  result->set_vector(vector);
  return result;
}

Vector* convert(double* vector, int dimension){
  Vector* result = new Vector(dimension);
  for(int i = 0; i < dimension; i++){
    result->set_element(i, vector[i]);
  }
  return result;
}

Vector* add(Vector* vector_a, Vector* vector_b){
  if(vector_a->get_dimension() != vector_b->get_dimension()){
    cout<<"mismatch of dimension"<<endl;
    return nullptr;
  }
  Vector* result = new Vector(vector_a->get_dimension());
  for(int i = 0; i < vector_a->get_dimension(); i++){
    result->set_element(i, vector_a->get_element(i) + vector_b->get_element(i));
  }
  return result;
}

Vector* subtract(Vector* vector_a, Vector* vector_b){
  if(vector_a->get_dimension() != vector_b->get_dimension()){
    cout<<"mismatch of dimension"<<endl;
    return nullptr;
  }
  Vector* result = new Vector(vector_a->get_dimension());
  for(int i = 0; i < vector_a->get_dimension(); i++){
    result->set_element(i, vector_a->get_element(i) - vector_b->get_element(i));
  }
  return result;
}
