#include <iostream>
#include <stdlib.h>

using namespace std;

int SIZE = 0;

enum sign{NEGATIVE = -1, POSITIVE = 1};

void init_Dynamic_Matrix(double ***matrix, bool I=false){
	if(!I){
		cout << "Input the size of array:";
		cin >> SIZE;
	}
	*matrix = new double*[SIZE];
	for(int i=0; i<SIZE; i++){
		matrix[0][i] = new double[SIZE];
	}
	if(!I)
		cout << "Now input the value of the matrix cell..." << endl;
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(!I){
				cout << "Input value of (" << i << "," << j << "): ";
				cin >> matrix[0][i][j];
			}else{
				if(i==j){
					matrix[0][i][j]=1;
				}else{
					matrix[0][i][j]=0;
				}
			}
		}
	}
}

void clearMem(double ***matrix){
	if(matrix[0]==NULL){
		return;
	}
	for(int i=0; i<SIZE; i++){
		delete []matrix[0][i];
	}
	delete matrix[0];
	matrix[0] = NULL;
	return;
}


void print_matrix(double **matrix, int size){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      cout<<matrix[i][j];
      if(j != size - 1){
        cout<<'\t';
      }
    }
    cout<<endl;
  }
}

void row_scaling(double **matrix, const int num_row, const double scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[num_row][i] *= scaler;
  }
}

void row_interchange(double **matrix, const int num_row_1, const int num_row_2){
  for(int i = 0; i < SIZE; i++){
    int temp = matrix[num_row_1][i];
    matrix[num_row_1][i] = matrix[num_row_2][i];
    matrix[num_row_2][i] = temp;
  }
}

void row_replacement(double **matrix, const int target_row, const int add_row, const double scaler){
  for(int i = 0; i < SIZE; i++){
    matrix[target_row][i] += matrix[add_row][i]*scaler;
  }
}


double matrix_determinent(double **matrix, int size, sign& s, double& scaler){
  //cout<<"function is run, size is "<<size<<endl;
  //print_matrix(matrix, size);
  if(size == 1){
    return matrix[0][0]*scaler*((s == POSITIVE)? 1 : -1);
  }
  else{
    if(matrix[size - 1][size - 1] != 0){
      //cout<<"row_scaling required"<<endl;
      scaler *=matrix[size - 1][size - 1];
      row_scaling(matrix, size - 1, 1.0/matrix[size - 1][size - 1]);
      //print_matrix(matrix, size);
    }
    else{
      //cout<<"row_interchange required"<<endl;
      int i = 0;
      for(; i < size - 1; i++){
        if(matrix[i][size - 1] != 0){
          break;
        }
      }
      row_interchange(matrix, i, size - 1);
      (s == POSITIVE)? s = NEGATIVE : s = POSITIVE; // change sign after row_interchange
      //cout<<"sign is "<<s<<endl;
      //print_matrix(matrix, size);
      if(matrix[size - 1][size - 1] != 1){
        //cout<<"row_scaling required"<<endl;
        scaler *=matrix[size - 1][size - 1];
        row_scaling(matrix, size - 1, static_cast<double>(1.0/matrix[size - 1][size - 1]));
        //print_matrix(matrix, size);
      }
    }
    //cout<<"row_replacement commencing"<<endl;
    for(int j = 0; j < size - 1; j++){
      if(matrix[j][size - 1] != 0){
        row_replacement(matrix, j, size - 1, -1.0*matrix[j][size - 1]);
      }
    }
    //print_matrix(matrix, size);
    return matrix_determinent(matrix, size - 1, s, scaler);
  }
}


void copy_matrix(double **matrix_scr, double **matrix_des){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      matrix_des[i][j] = matrix_scr[i][j];
    }
  }
}

void get_inverse(double **matrix_a, double **matrix_b){
  double **matrixForDeterminant = NULL;
  init_Dynamic_Matrix(&matrixForDeterminant, true);
  copy_matrix(matrix_a, matrixForDeterminant);
  sign s = POSITIVE;
  double scaler = 1;
  double determinant = matrix_determinent(matrixForDeterminant, SIZE, s, scaler);
  if( determinant == 0){
    cout<<"There is a singular matrix"<<endl;
	return;
  }
  cout<<endl<<"Determinant of matrix is "<<determinant<<endl<<endl;
  for(int j = 0; j < SIZE; j++){
    if(matrix_a[j][j] == 0){
      int i = j;
      for(; i < SIZE; i++){
        if(matrix_a[i][j] != 0){
          break;
        }
      }
      row_interchange(matrix_a, j, i);
      row_interchange(matrix_b, j, i);
    }
    double scaler = 1/matrix_a[j][j];
    if(scaler != 1){
      row_scaling(matrix_a, j, scaler);
      row_scaling(matrix_b, j, scaler);
    }
    for(int i = 0; i < SIZE; i++){ // row_replacement to create RREF
      if(i == j || matrix_a[i][j] == 0) continue;
      double scaler = -1.0*matrix_a[i][j];
      row_replacement(matrix_a, i, j, scaler);
      row_replacement(matrix_b, i, j, scaler);
    }
  }
  	cout << "Inverse Matrix is:" << endl << endl;
	print_matrix(matrix_b, SIZE);
	clearMem(&matrixForDeterminant);
}
/*
void multiply_matrix(double matrix_a[SIZE][SIZE_2], double matrix_b[SIZE_2][SIZE_3], double output[SIZE][SIZE_3]){
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE_3; j++)
      output[i][j] = 0;
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE_2; j++){
      for(int k = 0; k < SIZE_3; k++){
        output[i][k] += matrix_a[i][j]*matrix_b[j][k];
      }
    }
  }
}
*/

void getInputValue(double **matrix){

	cout << endl;
	cout << "=================================" << endl;
	cout << "Your input are:" << endl;
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			cout << matrix[i][j] << " ";
		}
	}
	cout << endl << "=================================" << endl;
	cout << endl << endl;

}



int main(){

	double **matrix_a = NULL;
	double **matrix_b = NULL;

	init_Dynamic_Matrix(&matrix_a);
	getInputValue(matrix_a);
	init_Dynamic_Matrix(&matrix_b, true);
	get_inverse(matrix_a, matrix_b);

	clearMem(&matrix_a);
	clearMem(&matrix_b);
	system("pause");

  return 0;
}
