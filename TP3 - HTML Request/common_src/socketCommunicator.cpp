#include "socketCommunicator.h"

#include <errno.h>
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

#include "socketException.h"

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

void SocketCommunicator::connect(const std::string& hostname,
                                 const std::string& port) {
  struct addrinfo* serv_info;

  if (_getaddrinfo(&serv_info, hostname.c_str(), port.c_str())) {
    throw SocketException();
  }

  struct addrinfo* head = serv_info;
  int connected = 0;

  for (; serv_info && !connected; serv_info = serv_info->ai_next) {
    int fd = socket(serv_info->ai_family, serv_info->ai_socktype,
                    serv_info->ai_protocol);
    if (::connect(fd, serv_info->ai_addr, serv_info->ai_addrlen) == -1) {
      ::close(fd);
    } else {
      connected = 1;
      this->fd = fd;
    }
  }

  freeaddrinfo(head);

  if (!connected) {
    throw SocketException();
  }
  return;
}

SocketCommunicator::SocketCommunicator(const std::string& hostname,
                                       const std::string& port) {
  connect(hostname, port);
}
SocketCommunicator::SocketCommunicator() { this->fd = -1; }

SocketCommunicator::SocketCommunicator(int fd) { this->fd = fd; }

SocketCommunicator& SocketCommunicator::operator=(SocketCommunicator&& other) {
  if (this != &other) {
    this->fd = other.fd;
    other.fd = -1;
  }

  return *this;
}

SocketCommunicator::SocketCommunicator(SocketCommunicator&& other) {
  this->fd = other.fd;
  other.fd = -1;
}

int SocketCommunicator::send(const char* message, unsigned int messageLength) {
  if (!message) {
    return 0;
  }

  unsigned int bytesSent = 0;
  int bytesPending = messageLength;

  while (bytesSent < messageLength) {
    int sent =
        ::send(this->fd, &message[bytesSent], bytesPending, MSG_NOSIGNAL);

    if (sent == -1) {
      throw SocketException();
    } else if (sent == 0) {
      break;
    }

    bytesSent += sent;
    bytesPending -= sent;
  }

  return bytesSent;
}

int SocketCommunicator::receive(std::stringbuf& buf) {
  int bytesReceived = 0;
  int bytes = 1;

  while (bytes > 0) {
    char buffer[64];
    bytes = recv(this->fd, buffer, 64, 0);

    if (bytes == -1) {
      std::cout << strerror(errno) << std::endl;
      throw SocketException();
    }

    if (bytes == 0) {
      break;
    }

    bytesReceived += bytes;
    buf.sputn(buffer, bytes);
  }

  return bytesReceived;
}

void SocketCommunicator::write_shutdown() { shutdown(this->fd, SHUT_WR); }

void SocketCommunicator::read_shutdown() { shutdown(this->fd, SHUT_RD); }

void SocketCommunicator::close() {
  ::close(this->fd);
  this->fd = -1;
}

SocketCommunicator::~SocketCommunicator() {
  if (this->fd != -1) {
    close();
  }
}
