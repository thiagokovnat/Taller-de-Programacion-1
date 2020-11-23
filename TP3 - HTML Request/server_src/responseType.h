#ifndef __RESPONSETYPE_H__
#define __RESPONSETYPE_H__
#include <string>

#include "HTTPRequest.h"
#include "protectedMap.h"

class ResponseType {
 public:
  virtual std::string respond(HTTPRequest request, ProtectedMap& resources) = 0;
  virtual ~ResponseType() = 0;
};

#endif
