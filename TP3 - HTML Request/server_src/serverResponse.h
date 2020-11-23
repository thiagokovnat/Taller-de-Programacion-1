#ifndef __SERVER_RESPONSE_H__
#define __SERVER_RESPONSE_H__
#include <string>

#include "HTTPRequest.h"
#include "protectedMap.h"
#include "responseType.h"

class ServerResponse {
 public:
  ResponseType* type;

  // Procesa una respuesta y devuelve la respuesta indicada por el tipo de
  // request.
  std::string processRequest(HTTPRequest request, ProtectedMap& resources);
};

#endif
