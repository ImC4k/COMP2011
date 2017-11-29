#include "combined.h"

int main(){
  cout<<"functions functioning well"<<endl;
  cout<<"Please input dimension of matrix"<<endl;
  int row, col;
  cin>>row>>col;
  Matrix* a = new Matrix(row, col);
  a->input_elements();
  cout<<"Your matrix is: "<<endl;
  a->print();
  a->update_determinant();
  cout<<"determinant of \"a\" is "<<a->get_determinant()<<endl;

  Matrix* b = inverse(a);
  b->print();
  Matrix* c = multiply_matrix_m(a, b);



  return 0;
}
