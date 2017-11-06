/* THE collatz conjecture */
/* conjecture theory:*/
/* take a number n, if it is even, then consider n/2*/
/* if it is odd, then consider 3n/2*/

/* No matter what number, the sequence must reach 1*/

#include <iostream>

using namespace std;

bool conjecture(int num){ // because of the conjecture, this function will not be infinite-recursion
  if(num == 1) return true;
  if(num % 2 == 0) return num/2;
  if(num % 2 == 1) return 3*num + 1;
  return false;
}

int main(){
  for(int i = 1; i <= 100; i++){
    cout<<boolalpha<<conjecture(i)<<endl;
  }

  return 0;
}
