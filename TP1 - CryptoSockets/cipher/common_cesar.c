#include "common_cesar.h"

#include <stdlib.h>
#include <string.h>

extern char* strdup();

// Inicializa la estructura cesar.
// Pre: self no es NULL
int cesar_init(cesar_cipher_t* self, int key) {
  if (!self) {
    printf("Error. No se aceptan parametros nulos.");
    return 1;
  }

  self->key = key;
  return 0;
}

// Encripta el mensaje indicado por message de tamanio messageLength
// Pre: Message y self no es NULL
void cesar_cipher(cesar_cipher_t* self, unsigned char* message,
                  unsigned int messageLength) {
  if (!self) {
    printf("Error. Se recibió un struct nulo");
    return;
  }

  int i = 0;
  while (i < messageLength) {
    message[i] = message[i] + self->key;
    i++;
  }
}

// Decripta el mensaje indicado por message de tamanio messageLength.
// Pre: self y message no son NULL
void cesar_decipher(cesar_cipher_t* self, unsigned char* message,
                    unsigned int messageLength) {
  if (!self) {
    printf("Error. Se recibio un struct nulo");
    return;
  }

  int i = 0;

  while (i < messageLength) {
    message[i] = message[i] - self->key;
    i++;
  }
}

// Destruye la estructura cesar, reiniciando su key a 0
// Pre: self no es NULL
void cesar_destroy(cesar_cipher_t* self) {
  if (!self) {
    return;
  }

  self->key = 0;
}
