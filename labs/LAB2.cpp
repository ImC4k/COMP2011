#include <iostream>

using namespace std;

int taxCalculator(){

  // NOTE: VARIABLE DECLARATION AREA
  

  while(true){
    // NOTE: RESET EVERYTHING BACK TO 0 OR SOMETHING NOT RELATED
    int tax_pay = 0;
    int income = 0;
    int marital_status = -1;
    int dep_kids = -1;
    int other_deduct = 0;
    int net_income = 0;
    char repeat_program = 'a';

    cout<<"==========================="<<endl;
    cout<<"An imaginary tax calculator"<<endl;
    cout<<"==========================="<<endl<<endl;

    // prompt users
    cout<<"1. Total income?"<<endl;
    cin>> income;
    while(cin.fail()){
      cout<<"Invalid input, please enter again."<<endl;
      cin.clear();
      cin.ignore(256,'\n');
      cin>> income;
    }
    cout<<endl<<endl;

    cout<<"2. Marital status?"<<endl;
    cout<<"Input 0 for single/widowed, 1 for married."<<endl;
    cin>> marital_status;
    while(cin.fail()||(marital_status<0 || marital_status>1)){
      cout<<"Invalid input, please enter again."<<endl;
      cin.clear();
      cin.ignore(256,'\n');
      cin>> marital_status;
    }
    cout<<endl<<endl;

    cout<<"3. Number of dependent kids?"<<endl;
    cin>> dep_kids;
    while(cin.fail()|| dep_kids <0){
      cout<<"Invalid input, please enter again."<<endl;
      cin.clear();
      cin.ignore(256,'\n');
      cin>> dep_kids;
    }
    cout<<endl<<endl;

    cout<<"4. Amount of other tax deduction to be claimed?"<<endl;
    cin>>other_deduct;
    while(cin.fail()||other_deduct<0){
      cout<<"Invalid input, please enter again."<<endl;
      cin.clear();
      cin.ignore(256,'\n');
      cin>> other_deduct;
    }
    cout<<endl<<endl;

    // calculate net chargeable income for different marital_status
    // if(marital_status==0)
    //   net_income = income - dep_kids*4000 - other_deduct;
    // else
    //   net_income = income - dep_kids*3000 - other_deduct;
    net_income = income - ((marital_status)? 3000:4000)*dep_kids - other_deduct;
    if(net_income <=0){
      tax_pay = 0;
      goto PRINT_TAX_STATEMENTS;
    }


    // debug
    // cout<<net_income<<endl;

    // tax calculation process part 1: within or for first 45000
    if(net_income>45000){
      tax_pay += 45000*0.02;
      net_income -= 45000;

      // debug
      // cout<<net_income<<endl;
      // cout<<tax_pay<<endl;
    }
    else{
      tax_pay += net_income*0.02;
      // continue;
      // debug
      // cout<<net_income<<endl;
      // cout<<tax_pay<<endl;
    }

    // tax calculation process part 2: within or for next 45000
    if(net_income > 45000){
      tax_pay += 45000*0.07;
      net_income-= 45000;
      // debug
      // cout<<net_income<<endl;
      // cout<<tax_pay<<endl;
    }
    else{
      tax_pay += net_income*0.07;
      // continue;
      // debug
      // cout<<net_income<<endl;
      // cout<<tax_pay<<endl;
    }

    // tax calculation process part 3: remaining income
    tax_pay += net_income*0.12;
    // debug
    // cout<<net_income<<endl;
    // cout<<tax_pay<<endl;

PRINT_TAX_STATEMENTS:
    // print final tax result to users
    cout<<"You need to pay $"<<tax_pay<<" tax."<<endl;
    cout<<"\n\n"<<endl;

    // prompt users for re-running program
    cout<<"Do you want to calculate another tax?"<<endl;
    cout<<"y for YES, n for no."<<endl;
    cin>>repeat_program;
    while(repeat_program != 'y' && repeat_program != 'n'){
      cout<<"Invalid input, please enter again."<<endl;
      cin>> repeat_program;
    }
    if (repeat_program =='y') {
      cout<<"\n\n\n\n\n\n\n\n\n\n"<<endl;
      continue; // re-run program
    }
    else if(repeat_program =='n'){
      cout<<"\n\n"<<endl;
      cout<<"Thanks for using TAX CALCULATOR"<<endl<<endl;
      break;
    } // escape program

  }

  return 0;
}

int main(){
  taxCalculator();
  return 0;
}
