#ifndef __CLIENT_LISTENER_H__
#define __CLIENT_LISTENER_H__

#include <vector>

#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "clientCommunicator.h"
#include "protectedMap.h"

class ClientListener : public Thread {
 private:
  SocketAccepter& serverSocket;
  ProtectedMap& resources;
  std::vector<ClientCommunicator*> peers;
  void threadDestructor();

 public:
  ClientListener(SocketAccepter& server, ProtectedMap& map);

  // Ejecuta la aceptacion de clientes.
  void run() override;
};

#endif
