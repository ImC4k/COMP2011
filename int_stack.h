#ifndef INT_STACK_H_
#define INT_STACK_H_

#include <iostream>
#include <cstdlib>

using namespace std;
const int BUFFER_SIZE = 5;

class int_stack{
private:
  int data[BUFFER_SIZE];
  int top_index;

public:
  int_stack();
  bool empty() const;
  bool full() const;
  int size() const;
  int top() const;

  void push(int);
  void pop();
};

#endif
