#include "common_vigenere.h"

#include <stdlib.h>
#include <string.h>

// Inicializa la estructura utilizada para el cifrado Vigenere.
// Pre: self y key no son NULL
int vigenere_init(vigenere_cipher_t* self, char* key) {
  if (!key) {
    printf("Error. Struct Vigenere no acepta claves nulas.");
    return 1;
  }

  self->key = key;
  self->index = 0;

  return 0;
}

// Destruye la estructura vigenere.
// Pre: self no es NULL
void vigenere_destroy(vigenere_cipher_t* self) {
  if (!self) {
    return;
  }

  self->key = NULL;
  self->index = 0;
}

// Encripta el mensaje indicado por message de tamanio messageLength
// Pre: self y message no son NULL
void vigenere_cipher(vigenere_cipher_t* self, unsigned char* message,
                     unsigned int messageLength) {
  if (!message) {
    printf("Error. Se recibio mensaje nulo.");
    return;
  }

  unsigned int lengthKey = strlen(self->key);

  for (int i = 0; i < messageLength; i++) {
    message[i] =
        message[i % messageLength] + self->key[self->index % lengthKey];
    self->index++;
  }
}

// Decripta el mensaje indicado por message de tamanio messageLength
// Pre: self y message no son NULL
void vigenere_decipher(vigenere_cipher_t* self, unsigned char* message,
                       unsigned int messageLength) {
  if (!message) {
    printf("Error. Se recibio mensaje nulo.");
    return;
  }

  unsigned int lengthKey = strlen(self->key);

  for (int i = 0; i < messageLength; i++) {
    message[i] =
        message[i % messageLength] - self->key[self->index % lengthKey];
    self->index++;
  }
}
