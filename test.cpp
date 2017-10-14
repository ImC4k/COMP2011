#include <iostream>

using namespace std;

int main(){
  const int size = 9;
  char input[size+1];
  cin.getline(input, size+1, '\n');
  cout<<input;
  return 0;
}
