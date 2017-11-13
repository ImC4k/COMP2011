#ifndef LL_H_
#define LL_H_

#include "ll_node.h"

class ll{
private:
  ll_node* nodes_head;
  int size;

public:
  ll(int num); // construct a linked list of size 1, always need to have a data
  ~ll(); // detroy the linked list
  void add_ll_node(int num); // add to last
  void insert_ll_node(int num, int pos); // insert a number(int) to a position(int)
  void edit_ll_node(int num, int pos); // edit a number(int) at a position(int)
  void delete_ll_node(int pos); // delete the node at position pos
  int ll_search(int num); // returns first appearing position of the number; -1 if not found
  void ll_search_and_edit(int old_num, int new_num); // search existance of num in linked list and
  void ll_print(); // print the linked list, each node is separated by '\t'
};

#endif

/*
NOTE: when implementing the functions, consider:
      1: when the linked list is NULL
      2: when handling the first node
      3: when handling node between nodes
      4: when handling the last node
*/
