#include "protectedResultCenter.h"

#include <iostream>
#include <map>
#include <mutex>
#include <string>

void ProtectedResultCenter::addAlphabetically(std::string file,
                                              std::string result) {
  std::unique_lock<std::mutex> lock(this->lock);

  this->result[file] =
      result;  // Map en C++ Ordena las keys por el operador < automaticamente.
}

void ProtectedResultCenter::printResult() {
  for (auto it : this->result) {
    std::cout << it.first << " " << it.second << std::endl;
  }
}
