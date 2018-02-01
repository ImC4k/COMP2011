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
  delete UT; delete UTU; delete b0;
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

  Vector* b = new Vector(data_ll_head->get_num_data());
  for(int i = 0; i < b->get_dimension(); i++){
    b->set_element(i, converted_ll[i][1]);
  }

  Matrix* A = new Matrix(data_ll_head->get_num_data(), degree + 1);
  for(int i = 0; i < A->get_num_row(); i++){
    for(int j = 0; j < A->get_num_col(); j++){
      A->set_element(i, j, pow(converted_ll[i][0], j));
    }
  }

  result = least_square(A, b);
  Vector* result_v = convert(result, degree + 1);
  delete[] result;
  return result_v;
}

Vector* projection(Vector* vector, Matrix* subspace){
  Vector* fit_dimension_vector = expand_dimension(vector, subspace->get_num_row());
  if(!fit_dimension_vector){
    cout<<"vector dimension larger than subspace dimension, not supported"<<endl;
    return nullptr;
  }
  Matrix* orth_m = orthogonalize(subspace);
  Vector* projected_v = new Vector(subspace->get_num_row());
  for(int i = 0; i < orth_m->get_num_col(); i++){ // loop through every vector in orthogonalized matrix
    Vector* temp = get_column(orth_m, i); // selects one vector from the matrix, scale it and add it to projected_v
    temp->scaling(dot(fit_dimension_vector, temp)/dot(temp, temp));
    projected_v->add(temp);
    delete temp;
  }
  delete fit_dimension_vector; delete orth_m;
  return projected_v;
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
  Matrix* orth_mat = new Matrix(matrix->get_num_row, matrix->get_num_col);
  for(int i = 0; i < matrix->get_num_col(); i++){ // loop through each vector
    /*  need to subtract vector from original vector
    *   eg u2 = x2 - x2->scaling(dot(x2, u1)/dot(u1, u1));
    *      u3 = x3 - x3->scaling(dot(x3, u1)/dot(u1, u1)) - x3->scaling(dot(x3, u2)/dot(u2, u2));
    *   for-loop required, add the orthogonalized vector into orth_mat immediately after,
    *   remember to delete the vector after adding into matrix, or else the vector will be lost
    */
    Vector* in_v = get_column(matrix, i); // the input vector to be processed
    Vector* orth_v = copy_v(in_v);
    for(int j = 0; j < orth_mat->get_num_row(); j++){ // loop through each element in a vector
      double orth_element = in_v->get_element(j);
      for(int k = 0; k < i; k++){ // count number of vectors to subtract
        Vector* subtract_vector = get_column(matrix, k);
        orth_element -= dot(in_v, subtract_vector)/dot(subtract_vector, subtract_vector)*subtract_vector->get_element(j);
        delete subtract_vector;
      }
      orth_v->set_element(j, orth_element);
    }
    orth_mat->set_column(orth_v, i);
    delete orth_v;
  }
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
