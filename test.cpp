#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//#include "tutorial1_c++.cpp"

using namespace std;

int print_maze(char maze[], const int HEIGHT, const int WIDTH){
  for(int i = 0; i<HEIGHT*WIDTH; i++){
    cout<<maze[i];
    if(i%WIDTH==17){
      cout<<endl;
    }
  }
  return 0;
}

int addNumber(int a, int b = 3){
  cout<<"a+b== "<< a+b<<endl;
  return a+b;
}

int addNumber(int a, int b, int c){ //test for overloading
  cout<<"a+b+c= "<<a+b+c<<endl;
  return a+b+c;
}

int loginPermission(){
  int in;
  cout<< "Type in password: " <<endl;
  cin >> in;
  if(in==347511){
    cout<< "Welcome Professor." <<endl;
    cout<< "You may proceed."<<endl;
    return 0;
  }
  else{
    cout<< "Error, intruder alert!" <<endl;
    return -1;
  }
}

int update(int &a, int b){
  int c = a;
  a+=b;
  return c;
}

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

  int in_a, in_b;
  cout<<"input 2 int to calculate multiplicative inverse"<<endl;
  cin>>in_a>>in_b;
  int out = gcd(in_a, in_b);
  cout<< "GCD of "<<in_a<<" and "<<in_b<<" is "<<out<<endl;
  if(gcd(in_a,in_b)!= 1){
    cout<<"There is no such inverse."<<endl;
    return 0;
  }
  cout<< "Inverse of "<<in_a<<" and "<<in_b<<" is "<< m_inverse(in_a, in_b)<<endl;


  return 0;
}
