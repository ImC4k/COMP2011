#include <iostream>

using namespace std;

int SIZE = 0;

enum sign{NEGATIVE = -1, POSITIVE = 1};



void print_matrix(double **matrix, int size){
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

void gen_matrix(double **matrix){
  for(int i = 0; i < SIZE*SIZE; i++){
    cout<<i+1<<", ";
  }
}

void init_Dynamic_Matrix(double ***matrix){
	cout << "Input the size of array:";
	cin >> SIZE;
	*matrix = new double*[SIZE];
	for(int i=0; i<SIZE; i++){
		matrix[0][i] = new double[SIZE];
	}
	cout << "Now input the value of the matrix cell..." << endl;
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			cout << "Input value of (" << i << "," << j << "): ";
			cin >> matrix[0][i][j];
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

int main(){
	
	double **matrix = NULL;
	init_Dynamic_Matrix(&matrix);

  sign s = POSITIVE;
  double scaler = 1;
  double determinent = matrix_determinent(matrix, SIZE, s, scaler);
  cout<<"determinent is "<<determinent<<endl;

	clearMem(&matrix);

  return 0;
}
