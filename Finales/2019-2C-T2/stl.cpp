#include <list>
#include <iostream>
#include <algorithm>

template<class T>
std::list<T> dobleSiNo(std::list<T> a, std::list<T> b){
  std::list<T> newList;

  for(T& elem: a){
    if(std::find(b.begin(), b.end(), elem) == b.end()){
      newList.push_back(elem);
      newList.push_back(elem);
    }
  }

  return newList;
}

int main(){
  std::list<int> a;
  std::list<int> b;

  for(int i = 0; i < 10; i++){
    if(i % 2 == 0){
      a.push_back(i);
      b.push_back(i);
    }else{
      a.push_back(i);
    }
  }

  std::list<int> test = dobleSiNo(a, b);
  for(auto& elem: test){
    std::cout<<elem<<std::endl;
  }

  return 0;
}
