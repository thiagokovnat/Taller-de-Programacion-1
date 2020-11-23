#include "server.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>

#include "../common_src/socket.h"
#include "../common_src/socketException.h"
#include "protectedMap.h"

int Server::run(const char* port, const char* rootfile) {
  SocketAccepter socket(port);
  std::ifstream rootFile(rootfile);

  std::string rootText;

  getline(rootFile, rootText, '\x1A');

  rootFile.close();

  this->resources.protected_insertion("/", rootText);

  ClientListener listener(socket, this->resources);
  listener.start();

  char keep;

  while ((keep = getchar()) != 'q') {
  }

  socket.close();

  listener.join();

  return 0;
}
