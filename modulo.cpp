#include <iostream>

using namespace std;

int gcd(int a, int b){
  if(a%b == 0)
  return b;
return gcd(b,a%b);
}

int m_inverse(const int TARGET, const int MOD_SPACE){
  if(gcd(TARGET,MOD_SPACE)!=1){
    cout<<"There is no such inverse."<<endl;
    return 0;
  }
  for(int i = 1; i< MOD_SPACE; i++){
    if((i*TARGET)%MOD_SPACE==1){
      return i;
    }
  }
  return -1;
}

int main(){
  int num1, num2;
  cout<<"Input 2 numbers: "<<endl;
  cin>>num1>>num2;
  if(num1>num2){
    int temp = num1;
    num1 = num2;
    num2 = temp;
  }
  cout<<"GCD of "<<num1<<" and "<<num2<< " is "<<gcd(num1, num2)<<endl;
  cout<<"Inverse of "<<num1<<" in modulo space "<<num2<<" is "<<m_inverse(num1,num2);
  return 0;
}
