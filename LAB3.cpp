#include <iostream>

using namespace std;

int task1_prompt(int &height, int &numCandle){
  // TODO: Handle error

  cout<<"\nPlease input the height of the candle: ";
  cin>>height;

  cout<<"\nPlease input the number of the candle: ";
  cin>>numCandle;

  return 0;
}

int task1(int height, int numCandle, int space){
  for(int i = 0; i<=height; i++){
    for(int j = 1; j<=space+1; j++){
      cout<<" ";
    }
    for(int k = 1; k<=numCandle*2; k++){
      if(i==0 && k%2==1){
        cout<<" ";
      }
      else if(k%2==0){
        cout<<")";
      }
      else{
        cout<<"(";
      }
    }
    cout<<endl;
  }
  return 0;
}

int task2_prompt(int &cakeLayer, int &heightBottomLayer, int &widthBottomLayer, char &crustSymbol, char &fillingSymbol){

  cout<<"\nPlease input the layers of the cake: ";
  cin>>cakeLayer;

  cout<<"\nPlease input the height of the borrom layer of the cake (which should be larger than 4): ";
  cin>>heightBottomLayer;
  while(heightBottomLayer<=4){
    cout<<"\nPlease enter a number larger than 4: ";
    cin.clear();
    cin>>heightBottomLayer;
  }

  cout<<"\nPlease input the width of the borrom layer of the cake (which should be an even number): ";
  cin>>widthBottomLayer;
  while(widthBottomLayer%2==1){
    cout<<"\nPlease enter even number of width for the cake: ";
    cin.clear();
    cin>>widthBottomLayer;
  }

  cout<<"\nPlease input the symbol for the crust of the cake: ";
  cin>>crustSymbol;

  cout<<"\nPlease input the symbol for the filling of the cake: ";
  cin>>fillingSymbol;

  return 0;
}

int task2(int cakeLayer, int heightBottomLayer, int widthBottomLayer, char crustSymbol, char fillingSymbol){
  if(cakeLayer-heightBottomLayer>=0 || 4*(cakeLayer)-widthBottomLayer>0){
    cout<<"Height or width is not large enough. Please try again."<<endl;
    //return 0;
  }
  // if(widthBottomLayer-4*(cakeLayer-1) ==0){
  //   cout<<"\nThe cake will be incomplete.\n";
  // }

  for(int i = 1; i<=cakeLayer; i++){  // Cake layer
    for(int j = 1; j<=heightBottomLayer-(cakeLayer-i); j++){ // Height layer
      for(int k = 1; k<=(cakeLayer-i)*2; k++){ // Upper layer spaces
          cout<<" ";
        }
      for (int m = 1; m<=widthBottomLayer-(cakeLayer-i)*4; m++){ // Width layer, print cake
        if(j==1 || j==heightBottomLayer-(cakeLayer-i)){
          cout<<crustSymbol;
        }
        else if(m==1 || m==(widthBottomLayer-(cakeLayer-i)*4)){
          cout<<crustSymbol;
        }
        else{
          cout<<fillingSymbol;
        }
      }
      cout<<endl;
    }
  }
  return 0;
}

int main(){
START_PROGRAM:
  // Variable declaration
  int userChoice;
  int space_added_for_top_layer = 0;

  // Prompt user choices
  cout<<"\nEnter these numbers, and I will draw you something!"<<endl;
  cout<<"1: Draw candles.\n"
  <<"2: Draw cakes with rectangle shape.\n"
  <<"3: Draw birthday cake with candles on it.\n"
  <<"0: Exit."<<endl;

  cout<<"Please input your selection: ";
  cin>>userChoice;

  // Task 1
  if(userChoice == 1){
    int height = 0, numCandle = 0;
    task1_prompt(height, numCandle);
    task1(height, numCandle, -2);
    goto START_PROGRAM;
  }
  // Task 2
  else if(userChoice == 2){
    int cakeLayer = 0, heightBottomLayer = 0, widthBottomLayer = 0, space_added_for_top_layer;
    char crustSymbol = 'a', fillingSymbol = 'a';
    task2_prompt(cakeLayer, heightBottomLayer, widthBottomLayer, crustSymbol, fillingSymbol);
    task2(cakeLayer, heightBottomLayer, widthBottomLayer, crustSymbol, fillingSymbol);
    goto START_PROGRAM;
  }
  // Task 3
  else if(userChoice == 3){
    int height_task1 = 0, numCandle = 0, cakeLayer = 0, heightBottomLayer = 0, widthBottomLayer = 0, space_added_for_top_layer = 0;
    char crustSymbol = 'a', fillingSymbol = 'a';
    task1_prompt(height_task1, numCandle);
    task2_prompt(cakeLayer, heightBottomLayer, widthBottomLayer, crustSymbol, fillingSymbol);
    space_added_for_top_layer = (cakeLayer-1)*2;
    if(numCandle<=(widthBottomLayer-(cakeLayer-1)*4)){
      cout<<"\n\n\n\n\nHappy Birthday!"<<endl;
    }
    else{
      cout<<"\nHeight or width is not large enough. Please try again."<<endl;
    }
    task1(height_task1, numCandle, space_added_for_top_layer);
    task2(cakeLayer, heightBottomLayer, widthBottomLayer, crustSymbol, fillingSymbol);
    goto START_PROGRAM;
  }

  else if(userChoice==0){
    return 0;
  }
  else goto START_PROGRAM;
}
