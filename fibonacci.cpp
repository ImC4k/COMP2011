#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;
// buggy version

double fibonacci_slow(int index){ // uses recursion
	if(index <= 0) return 0;
	else if(index == 1) return 1;
	else return fibonacci_slow(index - 1) + fibonacci_slow(index - 2);
}

double fibonacci_moderate(int index){ // uses loop
	double T0 = 0;
	double T1 = 1;
	double next;
	if(index == 0) return 0;
	else if(index == 1) return 1;
	else{
		for(int i = 2; i <= index; i++){
			next = T0 + T1;
			T0 = T1;
			T1 = next;
		}
	}
	return next;
}

double fibonacci_fast(int index){ // uses closed formula
	double result = (pow((1+sqrt(5))/2,index)-pow((1-sqrt(5))/2,index))/sqrt(5);
	return result;
}

int main(){
	int index;
	int result;
	clock_t t;
	cout<<"Input wanted index of fibonacci sequence: "<<endl;

	cin>>index;
	while(cin.fail()){
		cout<<"error, please re-enter:"<<endl;
		cin.clear();
		cin.ignore(256,'\n');
		cin>>index;
	}
	t = clock();
	result = fibonacci_slow(index);
	t = clock() - t;
	cout<<"Result: index "<<index<< " of fibonacci sequence is "<<result<<".\n\n"<<endl;
	cout<<"Time used by recursion is "<<t/CLOCKS_PER_SEC*1000<<" milliseconds, ("<<t<<" ticks).\n\n"<<endl;

	t = clock();
	result = fibonacci_moderate(index);
	t = clock() - t;
	// cout<<"Result: index "<<index<< " of fibonacci sequence is "<<result<<"."<<endl;
	cout<<"Time used by loop is "<<t/CLOCKS_PER_SEC*1000<<" milliseconds, ("<<t<<" ticks).\n\n"<<endl;

	t = clock();
	result = fibonacci_fast(index);
	t = clock() - t;
	// cout<<"Result: index "<<index<< " of fibonacci sequence is "<<result<<"."<<endl;
	cout<<"Time used by closed formula is "<<t/CLOCKS_PER_SEC*1000<<" milliseconds, ("<<t<<" ticks).\n\n"<<endl;

	return 0;
}
