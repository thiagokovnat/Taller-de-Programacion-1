#include "client.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "../common_src/socketException.h"

int Client::run(const char* host, const char* port) {
  SocketCommunicator socket(host, port);

  std::string line;

  while (std::cin.good()) {
    getline(std::cin, line, '\x1A');
  }

  socket.send(line.c_str(), line.size());

  socket.write_shutdown();
  std::stringbuf buf;

  socket.receive(buf);

  socket.read_shutdown();
  socket.close();
  std::string a = buf.str();
  std::cout << a;

  return 0;
}
