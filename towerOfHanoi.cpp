#include <iostream>

using namespace std;

void tower_of_hanoi(int num_discs, char pegA, char pegB, char pegC){
  if(num_discs == 0){
    return;
  }
  tower_of_hanoi(num_discs-1, pegA, pegC, pegB);

  cout << "move disc " << num_discs << " from peg "<< pegA<< " to peg "<< pegC<<endl;

  tower_of_hanoi(num_discs-1, pegB, pegA, pegC);
}

int main(){
  char pegA = 'A';
  char pegB = 'B';
  char pegC = 'C';
  tower_of_hanoi(4, pegA, pegB, pegC);
}
