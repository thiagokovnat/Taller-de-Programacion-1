#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__

#include <string>

class HTTPRequest {
 private:
  std::string method;
  std::string resource;
  std::string body;

 public:
  HTTPRequest();
  void setMethod(const std::string& method);
  void setResource(const std::string& resource);
  void setBody(const std::string& body);
  std::string getMethod();
  std::string getResource();
  std::string getBody();
};

#endif
