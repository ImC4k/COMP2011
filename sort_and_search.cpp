#include <iostream> // the bubble sort algorithm

using namespace std;

void bubble_sort(int* arr, int size){
  bool re_search_required = true;
  while(re_search_required){
    re_search_required = false;
    for(int i = 0; i < size-1; i++){
      if(arr[i] > arr[i+1]){
        int temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
        re_search_required = true;
      }
    }
  }
}

bool binary_search(int* arr, int size, int search_num){
  int search_index = size/2;
  int up_bound = size;
  int low_bound = 0;
  while(true){
    if(search_index == up_bound || search_index == low_bound){
      cout<<"no such number"<<endl;
      return false;
    }
    if(search_num == arr[search_index]){
      cout<<"number exists!"<<endl;
      return true;
    }
    else{
      if(search_num < arr[search_index]){
        up_bound = search_index;
        search_index = (low_bound + up_bound)/2;
      }
      else{ // search_num > arr[search_index]
        low_bound = search_index;
        search_index = (low_bound + up_bound)/2;
      }
    }
  }
}

void print_array(int* arr, int size){
  for(int i = 0; i < size; i++){
    cout<<arr[i]<<endl;
  }
}


int main(){
  int arr_size;
  cout<<"input size of data"<<endl;
  cin>>arr_size;
  arr_size = (int) arr_size;
  int *arr = new int[arr_size];

  cout<<"please input data, press enter to commit each data"<<endl;
  for(int i = 0; i < arr_size; i++){
    cin>>arr[i];
  }
  cout<<endl<<"********************"<<endl;
  bubble_sort(arr, arr_size);
  print_array(arr, arr_size);

  int search_num;
  cout<<"please enter number you want to search"<<endl;
  cin>>search_num;
  binary_search(arr, arr_size, search_num);

  delete[] arr;
  arr = NULL;

  return 0;
}
