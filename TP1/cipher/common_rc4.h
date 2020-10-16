#ifndef __COMMON_RC4_H__
#define __COMMON_RC4_H__

#include <stddef.h>
#include <stdio.h>

typedef struct rc4_struct {
  unsigned char* key;
  unsigned int i, j;
  unsigned char ksa[256];
} rc4_cipher_t;

// Inicializa la estructura necesaria para el cifrado RC4.
// Pre: self y key no es NULL
int rc4_init(rc4_cipher_t* self, char* key);

// Destruye la estructura rc4, volviendo a sus valores iniciales
// Pre: self no es NULL
void rc4_destroy(rc4_cipher_t* self);

// Encripta el mensaje indicado por message de tamanio messageLength
// Pre: self, message no son NULL
void rc4_cipher(rc4_cipher_t* self, unsigned char* message,
                unsigned int messageLength);

// Decripta el mensaje indicado por message de tamanio messageLength
// Pre: self y message no son NULL
void rc4_decipher(rc4_cipher_t* self, unsigned char* message,
                  unsigned int messageLength);

#endif
