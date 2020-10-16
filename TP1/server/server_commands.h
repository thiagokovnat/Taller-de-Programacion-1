#ifndef __SERVER_COMMANDS_H__
#define __SERVER_COMMANDS_H_
#include "common_socket.h"

typedef struct server {
  socket_t serverSocket;
  socket_t clientSocket;
} server_t;

// Inicializa el servidor haciendo bind al puerto port.
// Pre: self y port no son NULL
int server_create(server_t* self, char* port);

// Decifra mensajes cifrados en rc4.
// Pre: Key y self no son NULL
int server_rc4(server_t* self, char* key);

// Decifra mensajes cifrados en cesar.
// Pre: self y key no son NULL
int server_cesar(server_t* self, int key);

// Decifra mensajes cifrados en vigenere
// Pre: Key y self no son NULL
int server_vigenere(server_t* self, char* key);

// Cierra el servidor, haciendo close de sus sockets.
// Pre: self no es NULL
void server_close(server_t* self);
#endif
