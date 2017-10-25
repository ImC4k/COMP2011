#include <iostream>

using namespace std;

const int SIZE = 10;

enum sign{NEGATIVE = -1, POSITIVE = 1};


void print_matrix(double matrix[][SIZE], int size){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      cout<<matrix[i][j];
      if(j != size - 1){
        cout<<' ';
      }
    }
    cout<<endl;
  }
}

void row_scaling(double matrix[][SIZE], const int num_row, const double scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[num_row][i] *= scaler;
  }
}

void row_interchange(double matrix[][SIZE], const int num_row_1, const int num_row_2){
  for(int i = 0; i < SIZE; i++){
    int temp = matrix[num_row_1][i];
    matrix[num_row_1][i] = matrix[num_row_2][i];
    matrix[num_row_2][i] = temp;
  }
}

void row_replacement(double matrix[][SIZE], const int target_row, const int add_row, const double scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[target_row][i] += matrix[add_row][i]*scaler;
  }
}


double matrix_determinent(double matrix[][SIZE], int size, sign& s, double& scaler){
  cout<<"function is run, size is "<<size<<endl;
  print_matrix(matrix, size);
  if(size == 2){
    return (matrix[0][0]*matrix[1][1]-matrix[1][0]*matrix[0][1])*scaler*((s == POSITIVE)? 1 : -1);
  }
  else{
    if(matrix[size - 1][size - 1] != 0){
      cout<<"row_scaling required"<<endl;
      scaler *=matrix[size - 1][size - 1];
      row_scaling(matrix, size - 1, 1.0/matrix[size - 1][size - 1]);
      print_matrix(matrix, size);
    }
    else{
      cout<<"row_interchange required"<<endl;
      int i = 0;
      for(; i < size - 1; i++){
        if(matrix[i][size - 1] != 0){
          break;
        }
      }
      row_interchange(matrix, i, size - 1);
      (s == POSITIVE)? s = NEGATIVE : s = POSITIVE; // change sign after row_interchange
      cout<<"sign is "<<s<<endl;
      print_matrix(matrix, size);
      if(matrix[size - 1][size - 1] != 1){
        cout<<"row_scaling required"<<endl;
        scaler *=matrix[size - 1][size - 1];
        row_scaling(matrix, size - 1, static_cast<double>(1.0/matrix[size - 1][size - 1]));
        print_matrix(matrix, size);
      }
    }
    cout<<"row_replacement commencing"<<endl;
    for(int j = 0; j < size - 1; j++){
      if(matrix[j][size - 1] != 0){
        row_replacement(matrix, j, size - 1, -1.0*matrix[j][size - 1]);
      }
    }
    print_matrix(matrix, size);
    return matrix_determinent(matrix, size - 1, s, scaler);
  }
}

void gen_matrix(double matrix[SIZE][SIZE]){
  for(int i = 0; i < SIZE*SIZE; i++){
    cout<<i+1<<", ";
  }
}

int main(){
  // double matrix[][SIZE] = {{3, 0, 0, 2, 0},
  //                       {1, 0, -3, 0, 0},
  //                       {0, 1, 0, 0, 3},
  //                       {0, 0, 0, 1, 2},
  //                       {0, 3, 1, 0, 0}};

  // double matrix[][SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double matrix[][SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};

  sign s = POSITIVE;
  double scaler = 1;
  double determinent = matrix_determinent(matrix, SIZE, s, scaler);
  cout<<((s == POSITIVE)? 1 : -1)*scaler<<endl;
  cout<<"determinent is "<<determinent<<endl;


  return 0;
}
