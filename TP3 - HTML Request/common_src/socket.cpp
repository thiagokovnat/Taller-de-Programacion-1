#define _POSIX_C_SOURCE 201112L  // Habilita getaddrinfo
#include "socket.h"

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>

#include "socketCommunicator.h"
#include "socketException.h"
SocketAccepter::SocketAccepter(const std::string& port) { bind(port); }

static int _getaddrinfo(struct addrinfo** serv_info, const char* hostname,
                        const char* port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;

  int error = getaddrinfo(hostname, port, &hints, serv_info);

  if (error) {
    std::cerr << "getaddrinfo error" << std::endl;
  }

  return error;
}

void SocketAccepter::bind(const std::string& port) {
  struct addrinfo* serv_info;

  if (_getaddrinfo(&serv_info, NULL, port.c_str())) {
    throw SocketException();
  }

  int connected = 0;
  struct addrinfo* head = serv_info;

  for (; serv_info && !connected; serv_info = serv_info->ai_next) {
    int fd = socket(serv_info->ai_family, serv_info->ai_socktype,
                    serv_info->ai_protocol);

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    if (::bind(fd, serv_info->ai_addr, serv_info->ai_addrlen) == -1) {
      ::close(fd);
    } else {
      connected = 1;
      this->fd = fd;
    }
  }

  listen(this->fd, 10);
  freeaddrinfo(head);

  if (!connected) {
    throw SocketException();
  }

  return;
}

SocketCommunicator SocketAccepter::accept() {
  struct sockaddr_in address;
  socklen_t addressLength = (socklen_t)sizeof(address);

  int fd = ::accept(this->fd, (struct sockaddr*)&address, &addressLength);

  if (fd == -1) {
    throw SocketException();
  }

  return (SocketCommunicator(fd));
}

void SocketAccepter::close() {
  shutdown(this->fd, SHUT_RDWR);
  ::close(this->fd);
  this->fd = -1;
}

SocketAccepter::~SocketAccepter() {
  if (this->fd == -1) {
    return;
  }
  ::close(this->fd);
}
