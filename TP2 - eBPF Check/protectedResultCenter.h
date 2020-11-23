#ifndef __PROTECTEDRESULTCENTER_H__
#define __PROTECTEDRESULTCENTER_H__
#include <map>
#include <mutex>
#include <string>

class ProtectedResultCenter {
 private:
  std::mutex lock;
  std::map<std::string, std::string> result;

 public:
  void addAlphabetically(std::string file, std::string result);
  void printResult();
};

#endif
