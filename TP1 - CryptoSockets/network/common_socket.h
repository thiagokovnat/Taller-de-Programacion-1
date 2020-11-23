#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

typedef struct socket {
  int fd;
} socket_t;

// Inicializa la estructura socket.
// Pre: self no es NULL
void socket_init(socket_t* self);

// Intenta conectarse con hostname en el puerto port. Devuelve 1 si falla, 0
// caso contrario.
// Pre: self, hostname y port no son NULL
int socket_connect(socket_t* self, const char* hostname, const char* port);

// Intenta hacer bind and listen al puerto port. Devuelve 1 si falla, 0 caso
// contrario.
// Pre: self y port no son NULL
int socket_bind(socket_t* self, const char* port);

// Intenta aceptar un usuario. Devuelve 1 si falla, 0 caso contrario.
// Pre: self y server no son NULL
int socket_accept(socket_t* self, socket_t* server);

// Envia el mensaje referenciado por mensaje de tamaño messageLength. Devuelve
// la cantidad de bytes enviados.
// Pre: self, mensaje no son NULL
int socket_send(socket_t* self, const unsigned char* mensaje,
                unsigned int messageLength);

// Recibe y almacena en buffer de tamaño bufferLength. Devuelve la cantidad de
// bytes recibidos. Deja un NULL terminator en el buffer
// Pre: self y buffer no son NULL
int socket_receive(socket_t* self, unsigned char* buffer,
                   unsigned int bufferLength);

// Cierra el socket
// Pre: self no es NULL
void socket_close(socket_t* self);

#endif
