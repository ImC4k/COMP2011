#include <iostream>

using namespace std;

const int BOARD_SIZE = 4;

int getSmallestBlock(const int blocks[], int size) {
  if(size == 0){
    if(blocks[size] != 0){
      return size + 1;
    }
    else return BOARD_SIZE + 1;
  }
  else{
    int previous = getSmallestBlock(blocks, size - 1);
    if(previous != BOARD_SIZE + 1){
      return previous;
    }
    else if(blocks[size] != 0){
      return size + 1;
    }
    else return BOARD_SIZE + 1;
  }
  return 0;
}

int main(){
  int blocks[] = {0, 0, 0, 0};
  cout<<getSmallestBlock(blocks, BOARD_SIZE);
  return 0;
}
