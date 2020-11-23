#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "../common_src/socket.h"

class Client {
 public:
  // Ejecuta el cliente en el host y port dados.
  int run(const char* host, const char* port);
};

#endif
