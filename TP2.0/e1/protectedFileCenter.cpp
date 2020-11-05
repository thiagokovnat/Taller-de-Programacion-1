#include "protectedFileCenter.h"

#include <list>
#include <mutex>
#include <string>

ProtectedFileCenter::ProtectedFileCenter(std::list<std::string> files) {
  this->list = files;
}

std::string ProtectedFileCenter::popIfNotEmpty() {
  std::unique_lock<std::mutex> lock(this->lock);
  if (this->list.size() == 0) {
    return "";
  } else {
    std::string file = this->list.front();
    this->list.pop_front();
    return file;
  }
}
