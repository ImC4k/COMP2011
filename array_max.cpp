#include <iostream>

using namespace std;
const int SIZE = 10;

int array_max(int arr[], int size){
  if(size == 1){
    return arr[size - 1];
  }
  else{
    int previous_array_max = array_max(arr, size - 1);
    if(arr[size - 1] > previous_array_max){
      return arr[size - 1];
    }
    else return previous_array_max;
  }
}

int matrix_max(int arrs[][SIZE], int row, int col){
  if(row == 1){
    return array_max(arrs[row - 1], col-1);
  }
  else{
    int previous_matrix_max = matrix_max(arrs, row - 1, col);
    if(array_max(arrs[row - 1], col) > previous_matrix_max){
      return array_max(arrs[row - 1], col);
    }
    else return previous_matrix_max;
  }
}

int main(){

  int numbers[] = {1, 2, 4, 3, 5, 6, 7, 4, 9, 4};
  int $2D_numbers[][SIZE] = {{1, 2, 3, 4, 5, 6, 50, 8, 9, 10},
                            {23, 1, 2, 3, 4, 5, 6, 7, 7, 5},
                            {1, 2, 4, 3, 6, 8, 0, 5, 4, 3}};
  cout<<matrix_max($2D_numbers, 2, SIZE)<<endl;
}
