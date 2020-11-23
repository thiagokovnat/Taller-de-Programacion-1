#ifndef __SERVER_H__
#define __SERVER_H__
#include "../common_src/socket.h"
#include "clientListener.h"
#include "protectedMap.h"

class Server {
 private:
  ProtectedMap resources;

 public:
  // Ejecuta el servidor con el puerto especificado y el arhivo rootfile
  // dado.
  int run(const char* port, const char* rootfile);
};

#endif
