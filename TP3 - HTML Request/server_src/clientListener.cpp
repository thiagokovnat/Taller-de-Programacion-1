#include "clientListener.h"

#include <utility>
#include <vector>

#include "../common_src/socket.h"
#include "../common_src/socketCommunicator.h"
#include "../common_src/socketException.h"
#include "../common_src/thread.h"
#include "clientCommunicator.h"

ClientListener::ClientListener(SocketAccepter& server, ProtectedMap& map)
    : serverSocket(server), resources(map) {}

void ClientListener::run() {
  while (1) {
    try {
      ClientCommunicator* peer = new ClientCommunicator(
          std::move(serverSocket.accept()), this->resources);

      peer->start();
      this->peers.push_back(peer);
      threadDestructor();
    } catch (SocketException& e) {
      while (!this->peers.empty()) {
        threadDestructor();
      }
      break;
    }
  }
}

void ClientListener::threadDestructor() {
  {
    std::vector<ClientCommunicator*>::iterator it = this->peers.begin();

    while (it != this->peers.end()) {
      if (!(*it)->isAlive()) {
        (*it)->join();
        delete *it;
        it = this->peers.erase(it);
      } else {
        ++it;
      }
    }
  }
}
