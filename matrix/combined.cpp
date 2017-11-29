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
  // cout<<"matrix det "<<src->get_determinant()<<endl;
  double* solution = new double[src->get_num_col()];
  for(int i = -1; i < src->get_num_col(); i++){ solution[i] = -1;} // initialize return array to 0

  Vector* copy_vector = copy_v(vector->get_vector(), vector->get_dimension());

  for(int i = 0; i < src->get_num_col(); i++){ // solve for every vatiable, apply cramer's rule here
    Matrix* temp_matrix = copy_m(src->get_matrix(), src->get_num_row(), src->get_num_col());
    temp_matrix->substitute_vector(copy_vector, i);
    temp_matrix->update_determinant();
    // cout<<"cramer det"<<temp_matrix->get_determinant()<<endl;
    solution[i] = temp_matrix->get_determinant()/src->get_determinant();
    delete temp_matrix;
  }

  delete copy_vector;
  return solution;
}

double* least_square(Matrix* src, Vector* b){
  Matrix* UT = transpose(src);
  UT->print();
  cout<<"1 ok"<<endl;
  Matrix* UUT = multiply_matrix_m(UT, src);
  UUT->print();
  cout<<"2 ok"<<endl;
  Vector* b0 = multiply_matrix_v(UT, b);
  b0->print();
  cout<<"3 ok"<<endl;
  double* solution = solve_unknowns(UUT, b0);
  cout<<"4 ok"<<endl;
  return solution;
}
