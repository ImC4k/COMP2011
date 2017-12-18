#include "combined.h"

Vector* multiply_matrix_v(Matrix* matrix, Vector* vector){
  if(matrix->get_num_col() != vector->get_dimension()){
    cout<<"mismatch of dimension"<<endl;
    return nullptr;
  }
  Vector* result = new Vector(matrix->get_num_row());
  for(int i = 0; i < result->get_dimension(); i++){
    double product = 0;
    for(int j = 0; j < matrix->get_num_col(); j++){
      product += matrix->get_element(i, j)*vector->get_element(j);
    }
    result->set_element(i, product);
  }
  return result;
}

double* solve_unknowns(Matrix* src, Vector* vector){
  src->update_determinant();
  double* solution = new double[src->get_num_col()];
  for(int i = -1; i < src->get_num_col(); i++){ solution[i] = -1;} // initialize return array to 0

  Vector* copy_vector = copy_v(vector->get_vector(), vector->get_dimension());

  for(int i = 0; i < src->get_num_col(); i++){ // solve for every vatiable, apply cramer's rule here
    Matrix* temp_matrix = copy_m(src->get_matrix(), src->get_num_row(), src->get_num_col());
    temp_matrix->substitute_vector(copy_vector, i);
    temp_matrix->update_determinant();
    solution[i] = temp_matrix->get_determinant()/src->get_determinant();
    delete temp_matrix;
  }

  delete copy_vector;
  return solution;
}

double* least_square(Matrix* src, Vector* b){
  Matrix* UT = transpose(src);
  Matrix* UTU = multiply_matrix_m(UT, src);
  Vector* b0 = multiply_matrix_v(UT, b);
  double* solution = solve_unknowns(UTU, b0);
  return solution;
}

Vector* regression(int degree){ // given degree of approximation wanted
  // prompt for points
  ll_point_head* data_ll_head = input_points();
  data_ll_head->print_all_data();
  double* result = new double[degree + 1]; // store regression result in form of 2D array
  for(int i = 0; i < degree; i++){
    result[i] = 0;
  }
  double** converted_ll = convert_ll(data_ll_head);
  cout<<"converted_ll"<<endl;
  for(int i = 0; i < data_ll_head->get_num_data(); i++){
    for(int j = 0; j < 2; j++){
      cout<<converted_ll[i][j]<<"\t";
    }
    cout<<endl;
  }
  Vector* b = new Vector(data_ll_head->get_num_data());
  for(int i = 0; i < b->get_dimension(); i++){
    b->set_element(i, converted_ll[i][1]);
  }
  cout<<"b"<<endl;
  b->print();

  Matrix* A = new Matrix(data_ll_head->get_num_data(), degree + 1);
  for(int i = 0; i < A->get_num_row(); i++){
    for(int j = 0; j < A->get_num_col(); j++){
      A->set_element(i, j, pow(converted_ll[i][0], j));
    }
  }
  cout<<"A"<<endl;
  A->print();

  result = least_square(A, b);
  Vector* result_v = convert(result, degree + 1);
  delete[] result;
  return result_v;
}

Vector* projection(Vector* vector, Matrix* subspace){

  return nullptr;
  //TODO
}

Vector* get_column(Matrix* matrix, int num_col){
  if(num_col > matrix->get_num_col()){
    return nullptr;
  }
  Vector* column = new Vector(matrix->get_num_row());
  for(int i = 0; i < matrix->get_num_row(); i++){
    vector->set_element(i, matrix->get_element(i, num_col));
  }
  return column;
}

Matrix* orthogonalize(Matrix* matrix){ // for 3 vectors only
  if(matrix->get_num_col() < 2){
    cout<<"problem occured"<<endl;
    return nullptr;
  }
  if(!dot(get_column(matrix, 0), get_column(matrix, 1))){
    return matrix;
  }

  int dimension = matrix->get_num_row();
  Vector* u1 = new Vector(dimension);
  Vector* u2 = new Vector(dimension);
  Vector* u3 = new Vector(dimension);
  Vector* temp = new Vector(dimension);

  u1 = get_column(matrix, 0);
  temp->copy(u1->get_vector(), dimension);

  delete temp;
}

void Matrix::substitute_vector(Vector* vector, int num_col){
  if(vector->get_dimension() != num_row){
    cout<<"mismatch of dimension"<<endl;
    return;
  }
  for(int i = 0; i < num_row; i++){
    matrix[i][num_col] = vector->get_element(i);
  }
}
