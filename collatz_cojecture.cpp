/* THE collatz conjecture */
/* conjecture theory:*/
/* take a number n, if it is even, then consider n/2*/
/* if it is odd, then consider 3n+1 */

/* No matter what number, the sequence must reach 1*/

#include <iostream>

using namespace std;

bool conjecture(int num){ // because of the conjecture, this function will not be infinite-recursion
  if(num == 0){
    cout<<"not applicable to 0!"<<endl;
    return false;
  }
  if(num == 1) return true;
  if(num % 2 == 0) return conjecture(num/2);
  if(num % 2 == 1) return conjecture(3*num + 1);
  return false;
}

bool print_conjecture_loop(int num){
  if(num == 0){
    cout<<"not applicable to 0!"<<endl;
    return false;
  }
  else{

    while(num != 1){
      cout<<num<<'\t';
      if(num % 2 == 0){
        num /= 2;
      }
      else{
        num = 3*num+1;
      }
    }
    return true;
  }
}

int main(){
  for(int i = 1; i <= 100; i++){
    print_conjecture_loop(i);
    cout<<endl<<endl;
  }

  return 0;
}
