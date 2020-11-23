#ifndef __PROTECTED_MAP_H__
#define __PROTECTED_MAP_H__
#include <map>
#include <mutex>
#include <string>

class ProtectedMap {
 private:
  std::map<std::string, std::string> resources;
  std::mutex lock;

 public:
  ProtectedMap();

  // Inserta protegidamente un elemento al mapa
  void protected_insertion(const std::string& resource,
                           const std::string& body);

  // Obtiene protegidamente un elemento del mapa.
  std::string protected_get(const std::string& resource);
};

#endif
