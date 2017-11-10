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
  Date* new_date = new Date;
  new_date -> year = 4444;
  new_date -> month = 12;
  new_date -> day = 31;
  cout<<new_date->year<<endl<<new_date->month<<endl<<new_date->day<<endl<<endl;
  delete new_date;
  new_date = NULL;
  return 0;
}
