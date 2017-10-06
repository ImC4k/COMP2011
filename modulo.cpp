#include <iostrea>

using namespace std;

int gcd(int a, int b){
  if(a%b == 0)
  return b;
return gcd(b,a%b);
}

int m_inverse(const int TARGET, const int MOD_SPACE){
  if(gcd(TARGET,MOD_SPACE)!=1){
    cout<<"There is no such inverse."<<endl;
    return 0;
  }
  for(int i = 1; i< MOD_SPACE; i++){
    if((i*TARGET)%MOD_SPACE==1){
      return i;
    }
  }
  return -1;
}

int main(){

  return 0;
}
