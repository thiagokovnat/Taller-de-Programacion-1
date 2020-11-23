#include "clientCommunicator.h"

#include <iostream>
#include <string>
#include <utility>
#include "../common_src/socket.h"
#include "../common_src/socketCommunicator.h"
#include "../common_src/thread.h"
#include "HTTPRequest.h"
#include "protectedMap.h"
#include "protocolParser.h"
#include "serverResponse.h"

ClientCommunicator::ClientCommunicator(SocketCommunicator peer,
                                       ProtectedMap& map)
    : socket(std::move(peer)), resources(map), running(1) {}

void ClientCommunicator::run() {
  std::stringbuf buffer;
  this->socket.receive(buffer);
  this->socket.read_shutdown();

  std::string text = buffer.str();
  std::cout << text.substr(0, text.find_first_of("\n")) << std::endl;

  HTTPRequest request;
  ProtocolParser parser;

  parser(text, request);
  ServerResponse server;

  std::string response = server.processRequest(request, this->resources);

  this->socket.send(response.c_str(), response.size());
  this->socket.write_shutdown();
  this->running = 0;
}

int ClientCommunicator::isAlive() { return this->running == 0; }

ClientCommunicator::~ClientCommunicator() { this->socket.close(); }
