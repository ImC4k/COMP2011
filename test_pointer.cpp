#include <iostream>

using namespace std;

int main(){
  int a = 0;
  int *ptr = &a;
  int **ptr_ptr = &ptr;
  cout<<a<<endl;
  cout<<&a<<endl;
  cout<<ptr<<endl;
  cout<<*ptr<<endl;
  cout<<ptr_ptr<<endl;
  cout<<*ptr_ptr<<endl;
  cout<<**ptr_ptr<<endl;
  return 0;
}
