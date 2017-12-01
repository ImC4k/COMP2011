#include "matrix.h"
// #include "vector.h"
#include "combined.h"
#include "point.h"

int main(){
  cout<<"*******************************"<<endl;
  cout<<"*                             *"<<endl;
  cout<<"*      MATRIX CALCULATOR      *"<<endl;
  cout<<"*                             *"<<endl;
  cout<<"*******************************"<<endl;
  cout<<"\n\n\n\n";

START: {
  cout<<"*****************************************************"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"MATRIX FUNCTIONS:                                   *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"press:                                              *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"0 to quit program                                   *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"1 for matrix manipulation                           *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"2 for matrix multiplication                         *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"3 for finding determinant                           *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"4 for finding inverse                               *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"5 for solving linear equations (unique system only) *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"6 for finding regression of system                  *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"*****************************************************"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"VECTOR FUNCTIONS:                                   *"<<endl;
  cout<<"(coming soon)                                       *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"*****************************************************"<<endl<<endl<<endl;

  int choice;
  cin>>choice;
  switch(choice){
    case 0: goto END;
    case 1: goto MANIPULATE;
    case 2: goto MULTIPLY;
    case 3: goto DET;
    case 4: goto INV;
    case 5: goto SOLVE;
    case 6: goto LSQ;
    default: cout<<"idiot"; goto START;
  }
}

MANIPULATE: {
  cout<<"please input dimension of matrix: "<<endl<<endl;
  int num_row, num_col;
  cin>>num_row>>num_col;
  if(num_row == 0 || num_col == 0){
    cout<<"idiot"<<endl;
    goto MANIPULATE;
  }
  Matrix* A = new Matrix(num_row, num_col);
  A->input_elements();
  cout<<endl;

MANIPULATE_START:
  cout<<"*****************************************************"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"press:                                              *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"0 to quit this function                             *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"1 to print matrix                                   *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"2 for row-scaling                                   *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"3 for row-interchange                               *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"4 for row_replacement                               *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"5 for scaling matrix                                *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"6 for reset matrix                                  *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"7 for determinant                                   *"<<endl;
  cout<<"                                                    *"<<endl;
  cout<<"*****************************************************"<<endl<<endl<<endl;
  int choice_op;
  cin>>choice_op;
  switch(choice_op){
    case 0: delete A; break;
    case 1: A->print(); cout<<endl; goto MANIPULATE_START;
    case 2: {
      cout<<"please input row number and scaling factor: "<<endl<<endl;
      int num_row;
      double scaler;
      cin>>num_row>>scaler;
      A->row_scaling(num_row, scaler);
      goto MANIPULATE_START;
    }
    case 3: {
      cout<<"please input row numbers to swap: "<<endl<<endl;
      int row_1, row_2;
      cin>>row_1>>row_2;
      A->row_interchange(row_1, row_2);
      goto MANIPULATE_START;
    }
    case 4: {
      cout<<"please input row number to scale: "<<endl<<endl;
      int row_1, row_2;
      double scaler;
      cin>>row_1;
      cout<<"please input scaler to multiply: "<<endl<<endl;
      cin>>scaler;
      cout<<"please input target row number: "<<endl<<endl;
      cin>>row_2;
      A->row_replacement(row_2, row_1, scaler);
      goto MANIPULATE_START;
    }
    case 5: {
      cout<<"please input scaler to multiply: "<<endl<<endl;
      double scaler;
      cin>>scaler;
      A->multiply_scaler(scaler);
      goto MANIPULATE_START;
    }
    case 6: {
      RESET_START:
      cout<<"*****************************************************"<<endl;
      cout<<"                                                    *"<<endl;
      cout<<"how do you want to reset?                           *"<<endl;
      cout<<"                                                    *"<<endl;
      cout<<"0 for setting to 0s                                 *"<<endl;
      cout<<"                                                    *"<<endl;
      cout<<"1 for setting to identity matrix                    *"<<endl;
      cout<<"                                                    *"<<endl;
      cout<<"2 for setting to 1s                                 *"<<endl;
      cout<<"                                                    *"<<endl;
      cout<<"*****************************************************"<<endl<<endl<<endl;

      int reset_option;
      cin>>reset_option;
      if(reset_option < 0 || reset_option > 2){
        cout<<"idiot"<<endl;
        goto RESET_START;
      }
      A->reset(reset_option);
      goto MANIPULATE_START;
    }
    case 7: {
      A->update_determinant();
      cout<<"the determinant of matrix is "<<A->get_determinant()<<endl<<endl;
      goto MANIPULATE_START;
    }
    defaut: cout<<"idiot"<<endl; goto MANIPULATE_START;
  }
}
goto START;

MULTIPLY: {
  cout<<"please input dimension of first matrix: "<<endl<<endl;
  int num_row, num_col;
  cin>>num_row>>num_col;
  if(num_row == 0 || num_col == 0){
    cout<<"idiot"<<endl;
    goto MULTIPLY;
  }
  Matrix* A = new Matrix(num_row, num_col);
  A->input_elements();

  num_row = num_col = 0;
  cout<<"please input dimension of second matrix: "<<endl<<endl;
  cin>>num_row>>num_col;
  if(num_row == 0 || num_col == 0){
    cout<<"idiot"<<endl;
    goto MULTIPLY;
  }
  if(A->get_num_col() != num_row){
    cout<<"mismatch of dimension, please re-enter"<<endl<<endl;
    delete A;
    goto MULTIPLY;
  }

  Matrix* B = new Matrix(num_row, num_col);
  B->input_elements();

  Matrix* C = multiply_matrix_m(A, B);
  cout<<"resultant matrix is: "<<endl<<endl;
  C->print();
  cout<<endl;
  C->update_determinant();
  cout<<"determinant of matrix is "<<C->get_determinant()<<endl<<endl;

  delete A;
  delete B;
  delete C;
}
goto START;

DET: {
  cout<<"please input dimension of matrix: "<<endl<<endl;
  int num_row, num_col;
  cin>>num_row>>num_col;
  if(num_row == 0 || num_col == 0){
    cout<<"idiot"<<endl;
    goto DET;
  }
  Matrix* A = new Matrix(num_row, num_col);
  A->input_elements();
  A->update_determinant();
  cout<<"determinant of matrix is "<<A->get_determinant()<<endl<<endl;
  delete A;
}
goto START;

INV: {
  cout<<"please input dimension of matrix: "<<endl<<endl;
  int num_row, num_col;
  cin>>num_row>>num_col;
  if(num_row == 0 || num_col == 0){
    cout<<"idiot"<<endl;
    goto INV;
  }
  Matrix* A = new Matrix(num_row, num_col);
  A->input_elements();
  A->update_determinant();
  if(A->get_determinant() == 0){
    cout<<"there is no inverse for this matrix"<<endl;
    delete A;
    goto START;
  }

  Matrix* B = inverse(A);
  cout<<"inverse of matrix is "<<endl<<endl;
  B->print();
  cout<<endl;

  delete A;
  delete B;
}
goto START;

SOLVE: {
  cout<<"please input dimension of matrix: "<<endl<<endl;
  int num_row, num_col;
  cin>>num_row>>num_col;
  if(num_row == 0 || num_col == 0){
    cout<<"idiot"<<endl;
    goto SOLVE;
  }
  Matrix* A = new Matrix(num_row, num_col);
  A->input_elements();
  A->update_determinant();

  cout<<"please input dimension of vector: "<<endl<<endl;
  int dimension;
  cin>>dimension;
  if(dimension == 0){
    cout<<"idiot"<<endl;
    delete A;
    goto SOLVE;
  }
  if(dimension != A->get_num_row()){
    cout<<"mismatch of dimension, cannot solve"<<endl;
    delete A;
    goto START;
  }

  Vector* b = new Vector(dimension);
  b->input_elements();

  double* solution = solve_unknowns(A, b);
  Vector* solution_v = convert(solution, A->get_num_col());
  delete[] solution;
  cout<<"solution of system is: "<<endl<<endl;
  solution_v->print();

  delete A;
  delete b;
  delete solution_v;
}
goto START;

LSQ: {
  cout<<"please input degree of polynomial approximation: "<<endl<<endl;
  int degree;
  cin>>degree;
  if(degree == 0){
    cout<<"idiot"<<endl;
    goto LSQ;
  }
  Vector* solution = regression(degree);

  cout<<"approximation of system: "<<endl<<endl;
  cout<<"y = ";
  cout<<"("<<solution->get_element(0)<<") + ";
  if(solution->get_dimension() > 1){
    cout<<"("<<solution->get_element(1)<<") * x + ";
  }
  for(int i = 2; i < solution->get_dimension() - 1; i++){
    cout<<"("<<solution->get_element(i)<<") * x^"<<i<<" + ";
  }
  cout<<"("<<solution->get_element(solution->get_dimension() - 1)<<") * x^"<<(solution->get_dimension() - 1)<<endl<<endl;
}
goto START;

END:
  cout<<"GOODBYE!"<<endl;
  return 0;
}
