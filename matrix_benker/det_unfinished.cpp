#include <iostream>

using namespace std;

static const int size = 7;

int setDeterminant(int **arr, int size){
	
	int det = 0;
	int head[size] = {0};
	
	for(int i=0; i<size; i++){
		if(i%2)
			head[i] = arr[0][i] * -1;
		else
			head[i] = arr[0][i];
	}
	
	for(int x=0; x<size; x++){
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				if(i==0 || j == x){
					continue;
				}
				cout << arr[i][j] << "\t";
			}
			if(i==0){
				cout << endl << head[x];
			}
			cout << endl;
		}
	}
	return det;
}

void printMatrix(int arr[][size]){
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "============================================================" << endl;
}


void initPointer(int ***p, int s){
	*p = new int*[s];
	for(int i=0; i<s; i++){
		(*p)[i] = new int[s];
	}
	return;
}


void copyArr(int **p, int arr[][size], int s){
	for(int i=0; i<s; i++){
		for(int j=0; j<s; j++){
			p[i][j] = arr[i][j];
		}
	}
}


int main(){
	
	int arr[size][size] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49};
	
	
	int **p = NULL;
	initPointer(&p,size);
	copyArr(p, arr, size);
	printMatrix(arr);
	setDeterminant(p, size);
	return 0;
}
