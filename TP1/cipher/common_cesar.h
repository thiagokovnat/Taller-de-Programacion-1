#ifndef __COMMON_CESAR_H__
#define __COMMON_CESAR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cesar_struct {
  int key;
} cesar_cipher_t;

// Inicializa la estructura cesar.
// Pre: self no es NULL
int cesar_init(cesar_cipher_t* self, int key);

// Destruye la estructura cesar, reiniciando su key a 0
// Pre: self no es NULL
void cesar_destroy(cesar_cipher_t* self);

// Encripta el mensaje indicado por message de tamanio messageLength
// Pre: Message y self no es NULL
void cesar_cipher(cesar_cipher_t* self, unsigned char* message,
                  unsigned int messageLength);

// Decripta el mensaje indicado por message de tamanio messageLength.
// Pre: self y message no son NULL
void cesar_decipher(cesar_cipher_t* self, unsigned char* message,
                    unsigned int messageLength);

#endif
