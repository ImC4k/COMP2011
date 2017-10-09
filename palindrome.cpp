#include <iostream>
#include <cstring>

using namespace std;

bool palindrome(const char x[], int startPt, int endPt){
  if(x[startPt] != x[endPt]){
    return false;
  }
  if(startPt >= endPt){
    return true;
  }
  return palindrome(x, startPt+1, endPt-1);
}

bool palindrome_iterative(const char x[]){
  int j = 0;
  int k = strlen(x)-1;
  for(; j<k; ++j, --k){
    if(x[j] != x[k]){
      return false;
    }
  }
  return true;
}

int main(){
  const int MAX_LINE_LEN = 255;
  char whole_line[MAX_LINE_LEN+1];

  while(cin.getline(whole_line,MAX_LINE_LEN+1, '\n')){
    cout << boolalpha << palindrome(whole_line,0, strlen(whole_line-1)) << endl;
  }
  return 0;
}
