//============================================================================
// Name        : Lab1.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;
int main() {
 int month;
 double input;
 do{
  cout<<"Which month were you born in?"<<endl;
  cin>> input;
  month = (int) input;
  if(month < 1 || month > 12){
   cout<<"Oh. You must be... crazy! Bye!"<<endl;
   break;
  }
  else{
   cout<<"I see! You were born in ";
   switch(month){
   case 1: cout<<"January. Happy day for you!"<<endl; break;
   case 2: cout<<"Feburary. I like you!"<<endl; break;
   case 3: cout<<"March. :)"<<endl; break;
   case 4: cout<<"April. I don't like you!"<<endl; break;
   case 5: cout<<"May. Bless you!"<<endl; break;
   case 6: cout<<"June. I love you!"<<endl; break;
   case 7: cout<<"July. Happy holiday!"<<endl; break;
   case 8: cout<<"August. Happy holiday for you too!"<<endl; break;
   case 9: cout<<"September. Happy birth-month!"<<endl; break;
   case 10: cout<<"October. Happy coming birth-month!"<<endl; break;
   case 11: cout<<"November. Great!"<<endl; break;
   case 12: cout<<"December. Superb!"<<endl; break;
   }
  }
  cout<<"\n";
 }while(true);
 return 0;
}
