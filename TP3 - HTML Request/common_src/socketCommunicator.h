#ifndef __SOCKET_COMMUNICATOR_H__
#define __SOCKET_COMMUNICATOR_H__

#include <sstream>
#include <string>

class SocketCommunicator {
 private:
  int fd;
  // Conecta el socket al host y puerto especificados.
  void connect(const std::string& hostname, const std::string& port);

 public:
  SocketCommunicator(const std::string& hostname, const std::string& port);

  explicit SocketCommunicator(int fd);

  SocketCommunicator& operator=(SocketCommunicator&& other);
  SocketCommunicator();

  SocketCommunicator(SocketCommunicator&& other);

  // Envia un mensaje message de largo messageLength.
  // Pre: Message no es NULL
  int send(const char* message, unsigned int messageLength);

  // Recibe un mensaje y lo deja en el buffer.
  int receive(std::stringbuf& buffer);

  // Cierra el socket.
  void close();

  // Hace un shutdown de read.
  void read_shutdown();

  // Hace un shutdown de write.
  void write_shutdown();

  ~SocketCommunicator();
};

#endif
