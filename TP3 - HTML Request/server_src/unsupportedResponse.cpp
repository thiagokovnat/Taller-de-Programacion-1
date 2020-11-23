#include "unsupportedResponse.h"

#include <string>

#include "HTTPRequest.h"
#include "protectedMap.h"

std::string UnsupportedResponse::respond(HTTPRequest request,
                                         ProtectedMap& resources) {
  std::string method = request.getMethod();
  std::string answer = "HTTP/1.1 405 METHOD NOT ALLOWED\n\n";

  return answer + method + " es un comando desconocido\n";
}

UnsupportedResponse::~UnsupportedResponse() {}
