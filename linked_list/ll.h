#ifndef LL_H_
#define LL_H_

#include "ll_node.h"

class ll{
private:
  ll_node* nodes_head;
  int size;

public:
  ll(); // construct a linked list of size 1, always need to have a data
  ~ll(); // detroy the linked list
  void add_ll_node(int); // add to last
  void insert_ll_node(int, int); // insert a number(int) to a position(int)
  void edit_ll_node(int, int); // edit a number(int) at a position(int)
  void delete_ll_node(int);
  int ll_search(int); // returns first appearing position of the number; -1 if not found
  void ll_search_and_edit(int);

};

#endif

/*
NOTE: when implementing the functions, consider:
      1: when the linked list is NULL
      2: when handling the first node
      3: when handling node between nodes
      4: when handling the last node
*/
