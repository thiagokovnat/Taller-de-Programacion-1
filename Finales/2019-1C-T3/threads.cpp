#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

class Counter{
  std::mutex mutex;
  std::condition_variable cv;
  int counter = 0;
  int limit;
public:
  Counter(int max) : limit(max){}
  void operator=(const Counter& c) = delete;
  Counter(const Counter& c) = delete;

  bool countEven(){
    std::unique_lock<std::mutex> lock(mutex);
    while(counter % 2 != 0){
      cv.wait(lock);
    }

    if(counter <= limit){
      std::cout<<"Counter at count even: "<<counter<<std::endl;
      counter++;
      cv.notify_all();
      return true;
    }else{
      counter++;
      cv.notify_all();
      return false;
    }

  }

  bool countUneven(){
    std::unique_lock<std::mutex> lock(mutex);
    while(counter % 2 == 0){
      cv.wait(lock);
    }

    if(counter <= limit){
      std::cout<<"Counter at count Uneven: "<<counter<<std::endl;
      counter++;
      cv.notify_all();
      return true;
    }else{
      counter++;
      cv.notify_all();
      return false;
    }
  }
};

Counter c(100);

int main(){

  std::thread par([&](){
    while(c.countEven()){
      continue;
    }
  });
  std::thread impar([&](){
    while(c.countUneven()){
      continue;
    }
});

  par.join();
  impar.join();
  return 0;

}
