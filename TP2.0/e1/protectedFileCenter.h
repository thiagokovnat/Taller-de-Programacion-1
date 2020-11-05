#ifndef __PROTECTEDFILECENTER_H__
#define __PROTECTEDFILECENTER_H__
#include <list>
#include <mutex>
#include <string>

class ProtectedFileCenter {
 private:
  std::mutex lock;
  std::list<std::string> list;

 public:
  ProtectedFileCenter(std::list<std::string> files);
  std::string popIfNotEmpty();
};

#endif
