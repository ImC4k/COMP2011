#include <iostream>

using namespace std;

static const int size = 4;

int setDeterminant(int arr[][size], int size){
	
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


int main(){
	
	int arr[size][size] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	printMatrix(arr);
	setDeterminant(arr, size);
	return 0;
}
