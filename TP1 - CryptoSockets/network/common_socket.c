#include "common_socket.h"
#define _POSIX_C_SOURCE 201112L  // Habilita getaddrinfo
#include <arpa/inet.h>           // inet_ntop
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Inicializa la estructura socket.
// Pre: self no es NULL
void socket_init(socket_t* self) { self->fd = -1; }

// Usa la funcion getaddrinfo utilizando los mismos hints.
// Pre: port y serv_info no son NULL
int _getaddrinfo(struct addrinfo** serv_info, const char* hostname,
                 const char* port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;

  int error = getaddrinfo(hostname, port, &hints, serv_info);
  if (error) {
    printf("Error getaddrinfo.");
    return 1;
  }

  return 0;
}

// Intenta conectarse con hostname en el puerto port. Devuelve 1 si falla, 0
// caso contrario.
// Pre: self, hostname y port no son NULL
int socket_connect(socket_t* self, const char* hostname, const char* port) {
  struct addrinfo* serv_info;

  if (_getaddrinfo(&serv_info, hostname, port)) {
    return 1;
  }

  struct addrinfo* head = serv_info;
  int connected = 0;

  for (; serv_info && !connected; serv_info = serv_info->ai_next) {
    self->fd = socket(serv_info->ai_family, serv_info->ai_socktype,
                      serv_info->ai_protocol);
    if (connect(self->fd, serv_info->ai_addr, serv_info->ai_addrlen) == -1) {
      close(self->fd);
    } else {
      connected = 1;
    }
  }

  freeaddrinfo(head);
  return 0;
}

// Intenta hacer bind and listen al puerto port. Devuelve 1 si falla, 0 caso
// contrario.
// Pre: self y port no son NULL
int socket_bind(socket_t* self, const char* port) {
  struct addrinfo* serv_info;

  if (_getaddrinfo(&serv_info, NULL, port)) {
    return 1;
  }

  int connected = 0;
  struct addrinfo* head = serv_info;

  for (; serv_info && !connected; serv_info = serv_info->ai_next) {
    self->fd = socket(serv_info->ai_family, serv_info->ai_socktype,
                      serv_info->ai_protocol);

    int val = 1;
    setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    if (bind(self->fd, serv_info->ai_addr, serv_info->ai_addrlen) == -1) {
      printf("Hubo un error en el bind.\n");
      close(self->fd);
    } else {
      connected = 1;
    }
  }

  listen(self->fd, 10);
  freeaddrinfo(head);

  return 0;
}

// Intenta aceptar un usuario. Devuelve 1 si falla, 0 caso contrario.
// Pre: self y server no son NULL
int socket_accept(socket_t* self, socket_t* server) {
  struct sockaddr_in address;
  socklen_t addressLength = (socklen_t)sizeof(address);

  int fd = accept(server->fd, (struct sockaddr*)&address, &addressLength);
  self->fd = fd;

  return fd == -1;
}

// Envia el mensaje referenciado por mensaje de tamaño messageLength. Devuelve
// la cantidad de bytes enviados.
// Pre: self, mensaje no son NULL
int socket_send(socket_t* self, const unsigned char* mensaje,
                unsigned int messageLength) {
  if (messageLength == 0) {
    return 0;
  }

  int bytesPending = messageLength;
  int totalSent = 0;

  while (totalSent < messageLength) {
    int bytes = send(self->fd, &mensaje[totalSent], bytesPending, MSG_NOSIGNAL);

    if (bytes == -1 || bytes == 0) {
      break;
    }

    totalSent += bytes;
    bytesPending -= bytes;
  }

  return totalSent;
}

// Recibe y almacena en buffer de tamaño bufferLength. Devuelve la cantidad de
// bytes recibidos. Deja un NULL terminator en el buffer
// Pre: self y buffer no son NULL
int socket_receive(socket_t* self, unsigned char* buffer,
                   unsigned int bufferLength) {
  if (bufferLength == 0) {
    return 0;
  }

  int bytesAvailable = bufferLength - 1;
  int bytesReceived = 0;

  while (bytesReceived < bytesAvailable) {
    int bytes = recv(self->fd, &buffer[bytesReceived], bytesAvailable, 0);

    if (bytes == -1) {
      printf("Error. Receive recibio codigo de error -1. \n");
      return bytes;
    }

    if (bytes == 0) {
      break;
    }

    bytesReceived += bytes;
    bytesAvailable -= bytes;
  }

  buffer[bytesReceived] = 0;

  return bytesReceived;
}

// Cierra el socket
// Pre: self no es NULL
void socket_close(socket_t* self) {
  if (!self || self->fd == -1) {
    return;
  }

  shutdown(self->fd, SHUT_RDWR);
  close(self->fd);

  self->fd = -1;
}
