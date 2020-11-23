
#include "getResponse.h"

#include <iostream>
#include <string>

#include "HTTPRequest.h"
#include "protectedMap.h"

std::string GetResponse::respond(HTTPRequest request, ProtectedMap& resources) {
  std::string OK = "HTTP/1.1 200 OK\n";
  std::string CONTENT_TYPE = "Content-Type: text/html\n\n";
  std::string NOT_FOUND = "HTTP 404 NOT FOUND\n\n";

  std::string resource = request.getResource();
  std::string body = resources.protected_get(resource);

  if (resource.compare("/") == 0) {
    return OK + CONTENT_TYPE + body;
  }

  if (body.compare("") == 0) {
    return NOT_FOUND;
  }

  return OK + "\n" + body;
}

GetResponse::~GetResponse() {}
