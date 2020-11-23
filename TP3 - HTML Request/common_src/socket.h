#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <sstream>
#include <string>

#include "socketCommunicator.h"

class SocketAccepter {
 private:
  int fd;

  // Bindea el socket al puerto especificado.
  void bind(const std::string& port);

 public:
  // Crea un Socket Accepter y lo bindea al puerto dado.
  explicit SocketAccepter(const std::string& port);

  // Acepta un cliente y devuelve un Puntero al Socket creado
  SocketCommunicator accept();

  // Cierra el socket.
  void close();

  ~SocketAccepter();
};

#endif
