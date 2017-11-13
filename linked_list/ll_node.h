#ifndef LL_NODE_H_
#define LL_NODE_H_

#include "utils.h"

// template <typename T>

class ll_node {

private:
  int data; // to store information
  ll_node* next_ptr; // to store the pointer of next node

public:
  ll_node(int, ll_node* = nullptr);
  ~ll_node();
  void set_data(int);
  int get_data();
  void set_next_ptr(ll_node* next_ptr = nullptr); // set next node's address
  ll_node* get_next_ptr();
  // int main();

};
#endif
