#include <iostream>
using namespace std;

// int main(){
//   // lambda function
//   float a = 1.6, b = 2.7, c = 3.8;
//
//   auto f = [&, a](int x) mutable -> int{a *= x; b += x; return c = a+b;};
//
//   for(int k = 1; k < 3; ++k)
//     cout<<"a = "<<a<<"\tb = "<<b<<"\tc = "<<c<<"\tf("<<k<<") = "<<f(k)<<endl;
//
//   cout<<"a = "<<a<<"\tb = "<<b<<"\tc = "<<c<<endl;
//   return 0;
// }

int main(){

  int a = 1, b = 1, c = 1;

  auto f = [a, b, &c]() mutable{
    auto g = [a, &b, &c]() mutable{
      cout<<a<<b<<c<<endl;
      a = b = c = 4;
    };

    a = b = c = 3; g();
  };
  a = b = c = 2; f();
  cout<<a<<b<<c<<endl;
  return 0;
}
