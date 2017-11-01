#include <iostream>

using namespace std;

enum Gender{male, female};
enum Dept{CSE, ECE, MATH};

struct Date{
  unsigned int year;
  unsigned int month;
  unsigned int day;
};

struct Student_Record{
  char name[32];
  unsigned int id;
  Gender gender;
  Dept dept;
  Date entry;
};



int main(){
  Student_Record rec = {"Calvin", 20429422, male, CSE, {2017, 10, 30}};
  return 0;
}

int& pre_increment(int & x){
  x+=1;
  return x;
}

int post_increment(int & x){
  x+=1;
  return x-1;
}
