#include "serverResponse.h"

#include <iostream>
#include <string>

#include "getResponse.h"
#include "postResponse.h"
#include "unsupportedResponse.h"

std::string ServerResponse::processRequest(HTTPRequest request,
                                           ProtectedMap& resources) {
  std::string type = request.getMethod();
  std::string answer;

  if (type.compare("GET") == 0) {
    this->type = new GetResponse();

  } else if (type.compare("POST") == 0) {
    this->type = new PostResponse();
  } else {
    this->type = new UnsupportedResponse();
  }

  answer = this->type->respond(request, resources);
  delete this->type;

  return answer;
}
