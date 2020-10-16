#ifndef __COMMON_FILE_READER_H__
#define __COMMON_FILE_READER_H__
#include <stdio.h>

typedef struct file_reader {
  FILE* file;
} file_reader_t;

// Inicializa el file reader abriendo el archivo filepath. En caso de que
// filepath sea NULL se usa stdin
// Pre: self no es NULL
int file_reader_init(file_reader_t* self, char* filepath);

// Devuelve TRUE si se llego a un eof
// Pre: self no es NULL
int file_reader_eof_reached(file_reader_t* self);

// Lee bufLength bytes del archivo.
// Pre: buf y self no son NULL
int file_reader_read_chunk(file_reader_t* self, unsigned char* buf,
                           unsigned int bufLength);

// Destruye la estructura file reader.
// Pre: self no es NULL
void file_reader_destroy(file_reader_t* self);

#endif
