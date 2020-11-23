#include "protocolParser.h"

#include <iostream>
#include <sstream>
#include <string>

#include "HTTPRequest.h"

void ProtocolParser::parseMethodAndResource(std::string& text,
                                            HTTPRequest& request) {
  size_t pos = text.find_first_of(" ");
  std::string method = text.substr(0, pos);
  request.setMethod(method);
  text.erase(0, pos + 1);

  pos = text.find_first_of(" ");
  std::string resource = text.substr(0, pos);
  request.setResource(resource);
  text.erase(0, pos + 1);
}

void ProtocolParser::operator()(std::string text, HTTPRequest& request) {
  std::istringstream stream(text);
  std::string line;
  std::getline(stream, line);
  parseMethodAndResource(line, request);
  line.clear();

  std::getline(stream, line);
  while (line.find_first_not_of(" ") !=
         line.npos) {  // Busco la linea vacia que separa las claves del body;
    line.clear();
    std::getline(stream, line);
  }

  getline(stream, line, '\x1A');
  request.setBody(line);
}
