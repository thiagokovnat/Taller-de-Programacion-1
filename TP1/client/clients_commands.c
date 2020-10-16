#include <stdio.h>

#include "client_commands.h"
#include "common_cesar.h"
#include "common_file_reader.h"
#include "common_rc4.h"
#include "common_socket.h"
#include "common_vigenere.h"
#define BUF_MAX_LEN 64

// Crea un cliente e intenta conectarse al host en el puerto port.
// Pre: self, host y port no son NULL
int client_create(client_t* self, char* host, char* port) {
  socket_init(&self->socket);

  if (socket_connect(&self->socket, host, port)) {
    printf("Hubo un error a la hora de conectarse al servidor.");
    return 1;
  }

  return 0;
}

// Envia el mensaje del buf de tamaño bufLength.
// Pre: self y buf no es NULL
int client_send(client_t* self, unsigned char* buf, unsigned int bufLength) {
  return socket_send(&self->socket, (const unsigned char*)buf, bufLength);
}

// Cifra un mensaje con cesar y lo envia. Al finalizar, cierra el cliente.
// Pre: self no es NULL
int client_cesar(client_t* self, int key) {
  if (!self) {
    printf("Error. se recibio un parametro invalido.");
    return 1;
  }

  cesar_cipher_t cipher;
  cesar_init(&cipher, key);

  file_reader_t reader;
  file_reader_init(&reader, NULL);
  unsigned char msg[BUF_MAX_LEN];

  while (!file_reader_eof_reached(&reader)) {
    int bytesRead = file_reader_read_chunk(&reader, msg, BUF_MAX_LEN);

    if (bytesRead == -1) {
      printf("Error al leer el archivo indicado\n");
      return 1;
    }

    cesar_cipher(&cipher, msg, bytesRead);
    client_send(self, msg, bytesRead);
  }

  file_reader_destroy(&reader);
  client_close(self);
  return 0;
}

// Cifra un mensaje con rc4 y lo envia. Al finalizar, cierra el cliente.
// Pre: self y key no son NULL
int client_rc4(client_t* self, char* key) {
  if (!self || !key) {
    printf("Error. se recibio un parametro invalido.");
    return 1;
  }

  rc4_cipher_t cipher;
  rc4_init(&cipher, key);

  file_reader_t reader;
  file_reader_init(&reader, NULL);
  unsigned char msg[BUF_MAX_LEN];

  while (!file_reader_eof_reached(&reader)) {
    int bytesRead = file_reader_read_chunk(&reader, msg, BUF_MAX_LEN);

    if (bytesRead == -1) {
      printf("Error al leer el archivo indicado\n");
      return 1;
    }

    rc4_cipher(&cipher, msg, bytesRead);
    client_send(self, msg, bytesRead);
  }

  file_reader_destroy(&reader);
  client_close(self);
  return 0;
}

// Cifra un mensaje con vigenere y lo envia. Al finalizar, cierra el cliente.
// Pre: self no es NULL
int client_vigenere(client_t* self, char* key) {
  if (!self || !key) {
    printf("Error. se recibio un parametro invalido.");
    return 1;
  }

  vigenere_cipher_t cipher;
  vigenere_init(&cipher, key);

  file_reader_t reader;
  file_reader_init(&reader, NULL);
  unsigned char msg[BUF_MAX_LEN];

  while (!file_reader_eof_reached(&reader)) {
    int bytesRead = file_reader_read_chunk(&reader, msg, BUF_MAX_LEN);

    if (bytesRead == -1) {
      printf("Error al leer el archivo indicado\n");
      return 1;
    }

    vigenere_cipher(&cipher, msg, bytesRead);
    client_send(self, msg, bytesRead);
  }

  file_reader_destroy(&reader);
  client_close(self);
  return 0;
}

// Cifra un mensaje con cesar y lo envia. Al finalizar, cierra el cliente.
// Pre: self no es NULL
void client_close(client_t* self) {
  if (self) {
    socket_close(&self->socket);
  }
}
