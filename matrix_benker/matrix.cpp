#include <iostream>

#include "matrix.h"

//default constructor
matrix::matrix(){
	arr = NULL;
	r-size = -1;
	c-size = -1;
	determinant = -1;
}

//constructor with parameters
matrix::matrix(int **p, int row, int col){
	arr = p;
	r-size = row;
	c-size = col;
	determinant = -1;
}

//destructor
~matrix::matrix(){
	//to be continued....
	return;
}

//assign matrix
bool matrix::setMatrix(int **p, int row, int col){
	if(p==NULL){
		return false;
	}
	arr = p;
	r-size = row;
	c-size = col;
	return true;
}

//replace one element
bool matrix::replaceOne(int row, int col, int num){
	if(arr==NULL){
		return false;
	}
	p[row][col] = num;
	determinant = -1;
	return true;
}

//set and calculate determinant
int matrix::setDeterminant(){
	//to be continued...
	return -1;
}

//print the matrix
void matrix::printMatrix() const{
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	return;
}






