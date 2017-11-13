#include "ll.h"

ll::ll(){
  cout<<"type in number you want to store: "<<endl;
  int data;
  cin>>data;
  ll_node* node = new ll_node(data);
  size = 1;
  nodes_head = node;
}

ll::~ll(){
  ll_node* delete_p; // pointer to be deleted
  ll_node* temp_p; // for storing next node pointer later on
  delete_p = this->nodes_head;
  while(delete_p != nullptr){
    temp_p = delete_p->get_next_ptr();
    delete delete_p;
    delete_p = temp_p;
  }
}

void ll::add_ll_node(int num){
  if(this->nodes_head == NULL){
    ll_node* node = new ll_node(num);
    size = 1;
    nodes_head = node;
    return;
  }
  ll_node* temp_ptr = this->nodes_head;
  while(temp_ptr->get_next_ptr() != nullptr){
    temp_ptr = temp_ptr->get_next_ptr();
  }
  ll_node* new_node = new ll_node(num);
  temp_ptr->set_next_ptr(new_node);
  this->size++;
}

void ll::insert_ll_node(int num, int pos){
  if(pos >= this->size){ add_ll_node(num); return;}
  if(pos == 0){
    ll_node* new_node = new ll_node(num, this->nodes_head);
    this->nodes_head = new_node;
    this->size++;
    return;
  }
  ll_node* current_ptr = this->nodes_head;
  ll_node* next_ptr = current_ptr->get_next_ptr();
  for(int i = 0; i < pos-1; i++){ // considering size = 2 and pos = 1 onwards
    current_ptr = next_ptr;
    next_ptr = current_ptr->get_next_ptr();
  }
  ll_node* new_node = new ll_node(num, next_ptr);
  current_ptr->set_next_ptr(new_node);
  this->size++;
}

void ll::edit_ll_node(int num, int pos){
  if(pos >= this->size){cerr<<"Out of bound!"<<endl; return;}
  ll_node* current_ptr = this->nodes_head;
  for(int i = 0; i < pos; i++){
    current_ptr = current_ptr->get_next_ptr();
  }
  current_ptr->set_data(num);
}

void ll::delete_ll_node(int pos){
  if(pos >= size){cerr<<"Out of bound!"<<endl; return;}
  if(pos == 0){
    ll_node* temp_ptr = this->nodes_head->get_next_ptr();
    delete this->nodes_head;
    this->nodes_head = temp_ptr;
    this->size--;
    return;
  }
  ll_node* current_ptr = this->nodes_head;
  ll_node* previous_ptr = current_ptr;
  for(int i = 0; i < pos; i++){
    previous_ptr = current_ptr;
    current_ptr = current_ptr->get_next_ptr();
  }
  previous_ptr->get_next_ptr()->set_next_ptr(current_ptr->get_next_ptr());
  delete current_ptr;
  this->size--;
}

int ll::ll_search(int num){
  ll_node* current_ptr = this->nodes_head;
  int pos = 0;
  for(; current_ptr != nullptr; current_ptr = current_ptr->get_next_ptr()){
    if(current_ptr->get_data() == num){
      return pos;
    }
    pos++;
  }
  return -1;
}

void ll::ll_search_and_edit(int num){
  int search_result = ll_search(num);
  if(search_result == -1){
    cerr<<"No such number found!"<<endl;
    return;
  }
  edit_ll_node(num, search_result);
}
