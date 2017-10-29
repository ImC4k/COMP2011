#include <iostream>
#include <string>
#include <fstream>
using namespace std;



int task_1(string in, string out){
  ifstream input(in);
  if(!input){
    cerr<<"Error, no such file found!"<<endl;
    return -1;
  }

  ofstream output(out);
  if(!output){
    cerr<<"Error, no such file found!"<<endl;
    return -1;
  }
  // output.open(out);
  int count = 0;
  // if(input.get() != ' '){
  //   count++;
  // }
  char c;
  if(!input.eof()){
    c = input.get();
    if(c != ' ' && c != '\n') count++;
  }
  while(true){
    if(c == ' ' || c == '\n'){
      count++;
      if(!input.eof()) c = input.get();
      else break;
      if(c == ' ' || c == '\n') continue;
      continue;
    }
    if(!input.eof()) c = input.get();
    else break;
  }
  string count_s = to_string(count);
  char count_c[10] = "";
  for(int i = 0; i < count_s.length(); i++){
    count_c[i] = count_s[i];
  }
  output.write("text size : ", sizeof("text size : "));
  output.write(count_c, sizeof(count_c));
  output.put('\n');

  input.close();
  input.open(in);

  bool flag = false;
  input.get(c);
  while(!input.eof()){
    if(c == '\'' || c == ',' || c == '.' || c == '-' || c == '_' || c == '<'
    || c == '>' || c == '(' || c == ')' || c == '!' || c == '?' || c == '\\'
    || c == '\"' || c == ';' || c == ':'){
        c = ' ';
        flag = false;
    }
    else if(c == ' '){
      flag = true;
    }
    output.put(tolower(c));
    if(flag){
      output.put('\n');
      flag = false;
    }
    input.get(c);
  }
  input.close();
  output.close();


  return 0;
}

int main(){
  string in_file, out_file;
  cout<<"Please enter input filename: "<<endl;
  cin>>in_file;

  cout<<"Please enter output filename: "<<endl;
  cin>>out_file;

  // in_file = "official_test.txt";
  // in_file = "happy.txt";
  // out_file = "test.txt";
  task_1(in_file, out_file);


  return 0;
}
