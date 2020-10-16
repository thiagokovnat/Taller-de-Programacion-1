#ifndef __COMMON_ARGS_PARSER_H__
#define __COMMON_ARGS_PARSER_H__

typedef struct args_parser {
  char method[10];
  char key[10];
} args_parser_t;

// Deja en el campo method el metodo y en key la key pasada por linea de comando
// Pre: self y argv no son NULL
int args_parser_get_method_and_key(args_parser_t* self, int argc, char** argv);

#endif
