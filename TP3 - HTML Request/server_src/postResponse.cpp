#include "postResponse.h"

#include <iostream>
#include <string>

#include "HTTPRequest.h"
#include "protectedMap.h"

std::string PostResponse::respond(HTTPRequest request,
                                  ProtectedMap& resources) {
  std::string OK = "HTTP/1.1 200 OK\n\n";

  std::string FORBIDDEN = "HTTP/1.1 403 FORBIDDEN\n\n";

  std::string resource = request.getResource();
  std::string body = request.getBody();
  resources.protected_insertion(resource, body);

  if (resource.compare("/") == 0) {
    return FORBIDDEN;
  }

  return OK + body;
}

PostResponse::~PostResponse() {}
