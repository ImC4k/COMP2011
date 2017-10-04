#include <iostream>

using namespace std;

int CPACalculator(){
  char letterGrade;
  float totalNumGrade = 0.0;
  int inputCredit;
  int totalCourse= 0;
  int totalCredit;

  do{
    cout<<"No. of credits of your course (0 to stop): "<<endl;
    cin>>inputCredit;
    totalCredit += inputCredit;
    if(inputCredit == 0){
      break;
    }
    totalCourse++;
    cout<<"Your letter grade (A, B, C, D or F): "<<endl;
    cin>>letterGrade;
    if(letterGrade != 'A' && letterGrade != 'B' && letterGrade != 'C' && letterGrade != 'D' && letterGrade != 'F'){
      cout<<"Input invalid, please enter your grade again!"<<endl;
      totalCourse--;
      totalCredit-=inputCredit;
      continue;
    }
    switch (letterGrade) {
      case 'A': totalNumGrade += 4.0*inputCredit; break;
      case 'B': totalNumGrade += 3.0*inputCredit; break;
      case 'C': totalNumGrade += 2.0*inputCredit; break;
      case 'D': totalNumGrade += 1.0*inputCredit; break;
      case 'F': totalNumGrade += 0.0;
      default: break;
    }
  }while(inputCredit !=0);
  cout<<"You have taken a total of "<<totalCredit<<" credits..."<<endl;
  cout<<"and your GPA is "<<totalNumGrade/totalCredit<<"."<<endl;
  return 0;
}

int main(){

  CPACalculator();

  return 0;
}
