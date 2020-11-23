#include "common_rc4.h"

#include <stdlib.h>
#include <string.h>

extern char* strdup();

// Intercambia dos posiciones del array
// Pre: array no es NULL, i y j estan dentro del arraysize.
static void swap(unsigned char* array, int i, int j) {
  unsigned char temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

// Inicializa el keystream para el uso del cifrado
// Pre: array y key no son NULL
static void rc4_ksa_init(unsigned char* array, unsigned char* key) {
  if (!array || !key) {
    return;
  }

  int keyLength = strlen((char*)key);

  for (int i = 0; i < 256; i++) {
    array[i] = (unsigned char)i;
  }

  int j = 0;
  for (int i = 0; i < 256; i++) {
    j = (j + key[i % keyLength] + array[i]) % 256;
    swap(array, i, j);
  }
}

// Inicializa la estructura necesaria para el cifrado RC4.
// Pre: self y key no es NULL
int rc4_init(rc4_cipher_t* self, char* key) {
  if (!self || !key) {
    printf("Error. RC4 no acepta valores nulas");
    return 1;
  }

  self->key = (unsigned char*)key;
  self->i = 0;
  self->j = 0;

  rc4_ksa_init(self->ksa, self->key);

  return 0;
}

// Destruye la estructura rc4, volviendo a sus valores iniciales
// Pre: self no es NULL
void rc4_destroy(rc4_cipher_t* self) {
  if (!self) {
    return;
  }

  self->key = NULL;
  self->i = 0;
  self->j = 0;
}

// Devuelve el proximo valor para el XOR del cifrado.
static unsigned char nextKey(rc4_cipher_t* self) {
  if (!self) {
    return 0;
  }

  self->i = (self->i + 1) % 256;
  self->j = (self->j + self->ksa[self->i]) % 256;

  swap(self->ksa, self->i, self->j);

  return self->ksa[(self->ksa[self->i] + self->ksa[self->j]) % 256];
}

// Encripta el mensaje indicado por message de tamanio messageLength
// Pre: self, message no son NULL
void rc4_cipher(rc4_cipher_t* self, unsigned char* message,
                unsigned int messageLength) {
  if (!self) {
    printf("Error. RC4 Cipher no acepta structs nulos");
    return;
  }

  for (int i = 0; i < messageLength; i++) {
    message[i] ^= nextKey(self);
  }
}

// Decripta el mensaje indicado por message de tamanio messageLength
// Pre: self y message no son NULL
void rc4_decipher(rc4_cipher_t* self, unsigned char* message,
                  unsigned int messageLength) {
  rc4_cipher(self, message, messageLength);
}
