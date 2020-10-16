#ifndef __CLIENTS_COMMANDS_H__
#define __CLIENTS_COMMANDS_H__
#include "common_socket.h"

typedef struct client {
  socket_t socket;
} client_t;

// Crea un cliente e intenta conectarse al host en el puerto port.
// Pre: self, host y port no son NULL
int client_create(client_t* self, char* host, char* port);

// Envia el mensaje del buf de tamaño bufLength.
// Pre: self y buf no es NULL
int client_send(client_t* self, unsigned char* buf, unsigned int bufLength);

// Cierra el cliente.
// Pre: self no es NULL
void client_close(client_t* self);

// Cifra un mensaje con rc4 y lo envia. Al finalizar, cierra el cliente.
// Pre: self y key no son NULL
int client_rc4(client_t* self, char* key);

// Cifra un mensaje con cesar y lo envia. Al finalizar, cierra el cliente.
// Pre: self no es NULL
int client_cesar(client_t* self, int key);

// Cifra un mensaje con vigenere y lo envia. Al finalizar, cierra el cliente.
// Pre: self no es NULL
int client_vigenere(client_t* self, char* key);

#endif
