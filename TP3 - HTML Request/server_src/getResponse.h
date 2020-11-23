#ifndef __GET_RESPONSE_H__
#define __GET_RESPONSE_H__

#include <string>

#include "HTTPRequest.h"
#include "protectedMap.h"
#include "responseType.h"

class GetResponse : public ResponseType {
 public:
  // Genera una respuesta para el request
  std::string respond(HTTPRequest request, ProtectedMap& resources) override;
  ~GetResponse();
};

#endif
