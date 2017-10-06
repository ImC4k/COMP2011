#include <iostream>

using namespace std;

const int GAMEBOARDSIZE = 18;

const int SAMPLEGAMEBOARD[GAMEBOARDSIZE][GAMEBOARDSIZE] = {
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void printGameBoard(const int gameBoard[][GAMEBOARDSIZE]) {
	for(int i = 0; i< GAMEBOARDSIZE; i++){
		for(int j = 0; j< GAMEBOARDSIZE; j++){
			if(gameBoard[i][j])
				cout<<'X';
			else
				cout<<' ';
		}
		cout<<endl;
	}
}

int getLiveNeighbors(const int gameBoard[][GAMEBOARDSIZE], int x, int y) {

	int neighbors = 0;
	for(int i = x-1; i <= x+1; i++){
		for(int j = y-1; j<= y+1; j++){
			int scan_x;
			int scan_y;

			if(i < 0) scan_x = GAMEBOARDSIZE-1;
			else if(i > GAMEBOARDSIZE-1) scan_x = 0;
			else scan_x = i;

			if(j < 0) scan_y = GAMEBOARDSIZE-1;
			else if(j > GAMEBOARDSIZE-1) scan_y = 0;
			else scan_y = j;

			if(gameBoard[scan_x][scan_y] == 1){
				neighbors += 1;
			}
		}
	}
	if(gameBoard[x][y] == 1) neighbors -= 1;
	return neighbors;
}



int main(){

  printGameBoard(SAMPLEGAMEBOARD);
  cout<<endl;
  cout<<getLiveNeighbors(SAMPLEGAMEBOARD, 0, 1)<<endl;


  return 0;
}
