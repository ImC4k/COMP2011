#include <iostream>

using namespace std;

bool contains(const char* s, char c){
  if(s == nullptr || c == '\0') return false;
  if(*s == c){cout<<&c<<endl<<s<<endl; return true;}
  else return contains(++s, c);
}

int count_unique(char* s){
  if(s == nullptr) return 0;

}

int main(){
  char word[] = "hello";
  char* s = word;
  char c = '5';
  cout<<boolalpha<<contains(s, c)<<endl;
}
