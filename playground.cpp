#include <iostream>

using namespace std;

// int num_digits(int n = 0){
//   if(n/10 == 0){
//     return 1;
//   }
//   else{
//     return 1+ num_digits(n/10);
//   }
// }

// int reverse(int n, int d){
//   if(d == 0){
//     return n;
//   }
//   else{
//     int power = 1;
//     for(int i = 1; i < d; i++){
//       power *= 10;
//     }
//     return n%10*power+reverse(n/10, d-1);
//   }
// }

// int increment(int x, int step = 1){
//   return x+step;
// }




int i = 10;

void fun1(){
  cout<<i<<endl;
}

void fun2(){
  int i = 20;
  cout<<i<<endl;
}

int main(){
  int i = 5;
  cout<<i<<endl;
  fun1();
  fun2();
  return 0;
}
