#ifndef COMBINED_H_
#define COMBINED_H_

#include "utils.h"
#include "matrix.h"
#include "vector.h"
#include "point.h"


Vector* multiply_matrix_v(Matrix* matrix, Vector* vector);
double* solve_unknowns(Matrix* matrix, Vector* vector); // unique solution only
double* least_square(Matrix* matrix, Vector* b); // find least square values by inputting matrix and vector
Vector* regression(int polynomial_degree); // call this function for linear regression, import points from a file

#endif
