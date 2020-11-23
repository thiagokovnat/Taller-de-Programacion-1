
#include "protectedMap.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <mutex>
#include <string>

ProtectedMap::ProtectedMap() {}

void ProtectedMap::protected_insertion(const std::string& resource,
                                       const std::string& body) {
  std::unique_lock<std::mutex>(this->lock);

  this->resources[resource] = body;
}

std::string ProtectedMap::protected_get(const std::string& resource) {
  std::unique_lock<std::mutex>(this->lock);

  std::map<std::string, std::string>::iterator it;

  it = this->resources.find(resource);

  if (it == this->resources.end()) {
    return "";
  }

  return this->resources[resource];
}
