#ifndef __CLIENT_COMMUNICATOR_H__
#define __CLIENT_COMMUNICATOR_H__

#include "../common_src/socket.h"
#include "../common_src/socketCommunicator.h"
#include "../common_src/thread.h"
#include "protectedMap.h"

class ClientCommunicator : public Thread {
 private:
  SocketCommunicator socket;
  ProtectedMap& resources;
  int running;

 public:
  ClientCommunicator(SocketCommunicator peer, ProtectedMap& map);

  // Comprueba si se termino el servicio dado al cliente.
  int isAlive();

  // Ejecuta la comunicacion con el cliente.
  void run() override;
  ~ClientCommunicator();
};

#endif
