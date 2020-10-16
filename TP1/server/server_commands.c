#include "server_commands.h"

#include "common_cesar.h"
#include "common_rc4.h"
#include "common_socket.h"
#include "common_vigenere.h"

#define BUF_MAX_LEN 65

// Inicializa el servidor haciendo bind al puerto port.
// Pre: self y port no son NULL
int server_create(server_t* self, char* port) {
  if (!self) {
    return 1;
  }

  socket_init(&self->serverSocket);
  if (socket_bind(&self->serverSocket, port)) {
    printf("Error al crear el servidor");
    return 1;
  }

  socket_init(&self->clientSocket);
  // Me quedo esperando una conexion para el cliente. Si hay un error cierro el
  // socket del servidor.
  if (socket_accept(&self->clientSocket, &self->serverSocket)) {
    printf("Error al aceptar un cliente");
    socket_close(&self->serverSocket);
    return 1;
  }

  return 0;
}

// Recibe un mensaje y almacena en buf de tamaño bufLength
// Pre: self, buf no son NULL
int server_receive(server_t* self, unsigned char* buf, unsigned int bufLength) {
  return socket_receive(&self->clientSocket, buf, bufLength);
}

// Decifra mensajes cifrados en rc4.
// Pre: Key y self no son NULL
int server_rc4(server_t* self, char* key) {
  if (!self) {
    return 1;
  }

  int bytesReceived = 0;
  unsigned char buf[BUF_MAX_LEN];
  rc4_cipher_t cipher;
  rc4_init(&cipher, key);

  while ((bytesReceived = server_receive(self, buf, sizeof(buf))) > 0) {
    rc4_decipher(&cipher, buf, bytesReceived);
    printf("%s", buf);
  }
  printf("\n");

  rc4_destroy(&cipher);
  server_close(self);
  return 0;
}

// Decifra mensajes cifrados en cesar.
// Pre: self y key no son NULL
int server_cesar(server_t* self, int key) {
  if (!self) {
    return 1;
  }

  int bytesReceived = 0;
  unsigned char buf[BUF_MAX_LEN];
  cesar_cipher_t cipher;
  cesar_init(&cipher, key);

  while ((bytesReceived = server_receive(self, buf, sizeof(buf))) > 0) {
    cesar_decipher(&cipher, buf, bytesReceived);
    printf("%s", buf);
  }
  printf("\n");

  cesar_destroy(&cipher);
  server_close(self);
  return 0;
}

// Decifra mensajes cifrados en vigenere
// Pre: Key y self no son NULL
int server_vigenere(server_t* self, char* key) {
  if (!self || !key) {
    return 1;
  }

  int bytesReceived = 0;
  unsigned char buf[BUF_MAX_LEN];
  vigenere_cipher_t cipher;
  vigenere_init(&cipher, key);

  while ((bytesReceived = server_receive(self, buf, sizeof(buf))) > 0) {
    vigenere_decipher(&cipher, buf, bytesReceived);
    printf("%s", buf);
  }
  printf("\n");

  vigenere_destroy(&cipher);
  server_close(self);
  return 0;
}

// Cierra el servidor, haciendo close de sus sockets.
// Pre: self no es NULL
void server_close(server_t* self) {
  if (!self) {
    return;
  }

  socket_close(&self->clientSocket);
  socket_close(&self->serverSocket);
}
