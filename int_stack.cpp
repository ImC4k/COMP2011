#include "int_stack"

int_stack::int_stack(){
  top_index = -1;
}

bool int_stack::empty() const{
  return (top_index == -1);
}

bool int_stack::full() const{
  return (top_index == BUFFER_SIZE - 1);
}

int int_stack::size() const{
  return top_index + 1;
}

int int_stack::top() const{
  if(!empty()){
    return data[top_index];
  }
  cerr<<"Empty stack"<<endl;
}

void int_stack::push(int x){
  if(!full()){
    data[++top_index] = x;
  }
  else{
    cerr<<"Full stack"<<endl;
  }
}

void int_stack::pop)_{
  if(!empty()){
    --top_index;
  }
  else{
    cerr<<"Empty stack"<<endl;
  }
}
