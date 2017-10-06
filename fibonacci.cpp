#include <iostream>

using namespace std;
// buggy version

int fibonacci(int index){
	int out = 1;
	int previous1 = 0;
	int previous2 = 0;
	int i = 1;
	while(i<index){
		out = previous1 + previous2;
		i++;
		previous2 = previous1;
		previous1 = out;
	}
	return out;
}

int main(){
	int index;
	int result;
	cout<<"Input wanted index of fibonacci sequence: "<<endl;

	cin>>index;
	while(cin.fail()){
		cout<<"error, please re-enter:"<<endl;
		cin.clear();
		cin.ignore(256,'\n');
		cin>>index;
	}

	result = fibonacci(index);
	cout<<"Result: index "<<index<< " of fibonacci sequence is "<<result<<"."<<endl;
	return 0;
}
