#ifndef __COMMON_VIGENERE_H__
#define __COMMON_VIGENERE_H__

#include <stddef.h>
#include <stdio.h>

typedef struct vigenere_struct {
  char* key;
  unsigned int index;
} vigenere_cipher_t;

// Encripta el mensaje indicado por message de tamanio messageLength
// Pre: self y message no son NULL
void vigenere_cipher(vigenere_cipher_t* self, unsigned char* message,
                     unsigned int messageLength);

// Decripta el mensaje indicado por message de tamanio messageLength
// Pre: self y message no son NULL
void vigenere_decipher(vigenere_cipher_t* self, unsigned char* message,
                       unsigned int messageLength);

// Inicializa la estructura utilizada para el cifrado Vigenere.
// Pre: self y key no son NULL
int vigenere_init(vigenere_cipher_t* self, char* key);

// Destruye la estructura vigenere.
// Pre: self no es NULL
void vigenere_destroy(vigenere_cipher_t* self);

#endif
