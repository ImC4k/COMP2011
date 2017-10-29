#include <iostream>

using namespace std;

void printGameBoard(char s1, char s2, char s3, char s4, char s5, char s6, char s7, char s8, char s9, char s10, char s11, char s12, char s13, char s14, char s15, char s16){
	cout << "     |     |     |     " << endl;
	cout << "  " << s1 << "  |  " << s2 << "  |  " << s3 <<"  |  " << s4 << endl;
	cout << "_____|_____|_____|_____" << endl;
	cout << "     |     |     |     " << endl;
	cout << "  " << s1 << "  |  " << s2 << "  |  " << s3 <<"  |  " << s4 << endl;
	cout << "_____|_____|_____|_____" << endl;
	cout << "     |     |     |     " << endl;
	cout << "  " << s1 << "  |  " << s2 << "  |  " << s3 <<"  |  " << s4 << endl;
  cout << "_____|_____|_____|_____" << endl;
  cout << "  " << s1 << "  |  " << s2 << "  |  " << s3 <<"  |  " << s4 << endl;
	cout << "     |     |     |     " << endl;
}

int main(){
  char s1 = '.', s2 = '.', s3 = '.', s4 = '.', s5 = '.', s6 = '.', s7 = '.',
   s8 = '.', s9 = '.', s10 = '.', s11 = '.', s12 = '.', s13 = '.', s14 = '.', s15 = '.', s16 = '.';
   printGameBoard(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16);
  return 0;
}
