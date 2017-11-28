#include <iostream>

using namespace std;

class test{
private:
  int a;
public:
  void shout();
  test* create();
  int get_a();
};

void test::shout(){
  cout<<"haha"<<endl;
}

test* test::create(){
  test* temp = new test();
  temp->a = 10;
  temp->shout();
  return temp;
}

int test::get_a(){
  return this->a;
}

int main(){
  test* something = create();
  cout<<something<<endl;
  cout<<something->get_a()<<endl;
  return 0;
}
