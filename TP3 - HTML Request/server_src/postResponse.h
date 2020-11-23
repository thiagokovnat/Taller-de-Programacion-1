#ifndef __POST_RESPONSE_H__
#define __POST_RESPONSE_H__

#include <string>

#include "HTTPRequest.h"
#include "protectedMap.h"
#include "responseType.h"

class PostResponse : public ResponseType {
 public:
  // Genera una respuesta para el request
  std::string respond(HTTPRequest request, ProtectedMap& resources) override;
  ~PostResponse();
};

#endif
