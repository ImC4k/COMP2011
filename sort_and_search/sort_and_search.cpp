#include "sorting.h"

void bubble_sort(double* arr, int size){
  bool re_search_required = true;
  while(re_search_required){
    re_search_required = false;
    for(int i = 0; i < size-1; i++){
      if(arr[i] > arr[i+1]){
        double temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
        re_search_required = true;
      }
    }
  }
}

bool binary_search(double* arr, int size, double search_num){
  int search_index = size/2;
  int up_bound_index = size;
  int low_bound_index = 0;
  if(search_num == arr[0] || search_num == arr[size - 1]){
    cout<<"number exists!"<<endl;
    return true;
  }
  while(true){
    if(search_index == up_bound_index || search_index == low_bound_index){
      cout<<"no such number"<<endl;
      return false;
    }
    if(search_num == arr[search_index]){
      cout<<"number exists!"<<endl;
      return true;
    }
    else{
      if(search_num - arr[search_index] < 0){
        up_bound_index = search_index;
        search_index = (low_bound_index + up_bound_index)/2;
      }
      else{ // search_num > arr[search_index], equivalently search_num - arr[search_index] > 0
        low_bound_index = search_index;
        search_index = (low_bound_index + up_bound_index)/2;
      }
    }
  }
}

void print_array(double* arr, int size){
  for(int i = 0; i < size; i++){
    cout<<arr[i]<<endl;
  }
}
