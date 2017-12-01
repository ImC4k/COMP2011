#include "point.h"

ll_point_head::ll_point_head(){
  head_data = nullptr;
  num_data = 0;
}

ll_point_head::~ll_point_head(){
  for(ll_point* temp_data = head_data; temp_data != nullptr;){
    ll_point* to_be_deleted_data = temp_data;
    temp_data = temp_data->next_data;
    delete to_be_deleted_data;
  }
}

ll_point* ll_point_head::get_head_data(){
  return head_data;
}

ll_point* ll_point_head::get_last_data(){
  if(head_data == nullptr){
    return nullptr;
  }

  ll_point* result = head_data;
  for(; result->next_data != nullptr; result = result->next_data)
  ;
  return result;
}

int ll_point_head::get_num_data(){
  return num_data;
}

void ll_point_head::add_to_last(ll_point* src){
  ll_point* last_data = get_last_data();
  if(last_data == nullptr){ // there is no head_data yet
    head_data = src;
    num_data++;
    return;
  }
  last_data->next_data = src;
  num_data++;
}

void ll_point_head::print_all_data(){
  ll_point* temp_ll = head_data;
  while(temp_ll != nullptr){
    cout<<temp_ll->data.x<<"\t"<<temp_ll->data.y<<endl;
    temp_ll = temp_ll->next_data;
  }
}





ll_point_head* input_points(){
  ll_point_head* data_ll_head = new ll_point_head();
  double x = 0, y = 0;
  char choice;
  do{
    choice = 'a';
    cout<<"please input points: "<<endl;
    cin>>x>>y;
    ll_point* data_ll = new ll_point;
    data_ll->data.x = x;
    data_ll->data.y = y;
    data_ll->next_data = nullptr;

    data_ll_head->add_to_last(data_ll);
    x = y = 0;
    cout<<"input another point? y or n"<<endl;
    cin>>choice;
  }while(choice == 'y');

  return data_ll_head;
}


double** convert_ll(ll_point_head* src){
  double** result = new double* [src->get_num_data()];
  for(int i = 0; i < src->get_num_data(); i++){
    result[i] = new double[2];
    result[i][0] = 0;
    result[i][1] = 0;
  }

  int i = 0;
  for(ll_point* temp_data = src->get_head_data(); temp_data != nullptr; temp_data = temp_data->next_data){
    result[i][0] = temp_data->data.x;
    result[i][1] = temp_data->data.y;
    i++;
  }

  return result;
}
