#include <stdio.h>

#include "../common_src/socket.h"
#include "clientListener.h"
#include "protectedMap.h"
#include "server.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    return 1;
  }

  Server server;

  server.run(argv[1], argv[2]);
}
