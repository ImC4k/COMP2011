#include <iostream> // the bubble sort algorithm
#include "sorting.h"

using namespace std;


int main(){
  int arr_size;
  cout<<"input size of data"<<endl;
  cin>>arr_size;
  arr_size = (int) arr_size;
  double *arr = new double[arr_size];

  cout<<"please input data, press enter to commit each data"<<endl;
  for(int i = 0; i < arr_size; i++){
    cin>>arr[i];
  }
  cout<<endl<<"********************"<<endl;
  bubble_sort(arr, arr_size);
  print_array(arr, arr_size);

  double search_num;
  cout<<"please enter number you want to search"<<endl;
  cin>>search_num;
  binary_search(arr, arr_size, search_num);

  delete[] arr;
  arr = NULL;

  return 0;
}
