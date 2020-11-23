#ifndef __PROTOCOL_PARSER_H__
#define __PROTOCOL_PARSER_H__
#include <sstream>
#include <string>

#include "HTTPRequest.h"

class ProtocolParser {
 private:
  void parseMethodAndResource(std::string& text, HTTPRequest& request);

 public:
  void operator()(std::string text, HTTPRequest& request);
  // Parsea una peticion http dejando sus contenidos en la variable request
};

#endif
