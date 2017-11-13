#include "ll.h"

int main(){
  cout<<"type in number you want to store: "<<endl;
  int num;
  cin>>num;
  ll* ll_1 = new ll(num);
  ll_1->add_ll_node(3);
  ll_1->add_ll_node(4);
  ll_1->add_ll_node(3);
  ll_1->add_ll_node(4);
  ll_1->add_ll_node(3);
  ll_1->add_ll_node(4);
  ll_1->ll_print();
  ll_1->delete_ll_node(0);
  ll_1->ll_print();
}
