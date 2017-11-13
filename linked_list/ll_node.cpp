#include "ll_node.h"

ll_node::ll_node(int data, ll_node* next_ptr){
  this->data = data;
  this->next_ptr = next_ptr;
}

ll_node::~ll_node(){
  // if(this != nullptr)
  //   delete this;
  // this->next_ptr = nullptr;
}

void ll_node::set_data(int data){
  this->data = data;
}

int ll_node::get_data(){
  return this->data;
}

void ll_node::set_next_ptr(ll_node* next_ptr){
  this->next_ptr = next_ptr;
}

ll_node* ll_node::get_next_ptr(){
  return this->next_ptr;
}

// int ll_node::main(){
//   cout<<"hi"<<endl;
//   return 0;
// }
