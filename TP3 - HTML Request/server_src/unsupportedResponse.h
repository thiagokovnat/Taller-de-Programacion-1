#ifndef __UNSUPPORTED_RESPONSE_H__
#define __UNSUPPORTED_RESPONSE_H__

#include <string>

#include "HTTPRequest.h"
#include "protectedMap.h"
#include "responseType.h"

class UnsupportedResponse : public ResponseType {
 public:
  // Devuelve una respuesta para el tipo de request dado.
  std::string respond(HTTPRequest request, ProtectedMap& resources) override;
  ~UnsupportedResponse();
};

#endif
