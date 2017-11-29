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
  double* solution = new double[src->get_num_col()];
  for(int i = 0; i < src->get_num_col(); i++){ solution[i] = 0;} // initialize return array to 0

  Vector* copy_vector = copy_v(vector->get_vector(), vector->get_dimension());

  for(int i = 0; i < src->get_num_col(); i++){ // solve for every vatiable, apply cramer's rule here
    Matrix* temp_matrix = copy_m(src->get_matrix(), src->get_num_row(), src->get_num_col());
    temp_matrix->substitute_vector(copy_vector, i);
    solution[i] = temp_matrix->get_determinant()/src->get_determinant();
    delete temp_matrix;
  }

  delete copy_vector;
  return solution;
}

double* least_square(Matrix* src, Vector* x, Vector* b){
  Matrix* UT = transpose(src);
  Matrix* UUT = multiply_matrix_m(src, UT);
  // Vector* b0 =
  return 0;
}
