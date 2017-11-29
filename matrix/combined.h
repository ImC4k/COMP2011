#include "matrix.h"

Vector* multiply_matrix_v(Matrix* matrix, Vector* vector);
double* solve_unknowns(Matrix* matrix, Vector* vector);
double* least_square(Matrix* matrix, Vector* x, Vector* b); // find least square values
