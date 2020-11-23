#include <algorithm>
#include <iostream>

#include "../common_src/socket.h"
#include "../common_src/socketException.h"
#include "client.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    return 0;
  }

  Client client;

  try {
    client.run(argv[1], argv[2]);
  } catch (SocketException& e) {
    std::cout << e.what() << std::endl;
  }
}
