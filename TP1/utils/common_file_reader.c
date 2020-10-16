#include "common_file_reader.h"

#include <stdio.h>
#define READ_MODE "r"

// Inicializa el file reader abriendo el archivo filepath. En caso de que
// filepath sea NULL se usa stdin
// Pre: self no es NULL
int file_reader_init(file_reader_t* self, char* filepath) {
  if (filepath) {
    self->file = fopen(filepath, READ_MODE);
    return self->file == NULL;
  }

  self->file = stdin;
  return 0;
}

// Devuelve TRUE si se llego a un eof
// Pre: self no es NULL
int file_reader_eof_reached(file_reader_t* self) { return feof(self->file); }

// Lee bufLength bytes del archivo.
// Pre: buf y self no son NULL
int file_reader_read_chunk(file_reader_t* self, unsigned char* buf,
                           unsigned int bufLength) {
  if (!self) {
    return -1;
  }

  int bytesRead = fread(buf, 1, bufLength, self->file);
  return bytesRead;
}

// Destruye la estructura file reader.
// Pre: self no es NULL
void file_reader_destroy(file_reader_t* self) {
  if (self->file != stdin) {
    fclose(self->file);
  }

  return;
}
