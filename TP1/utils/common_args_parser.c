#include "common_args_parser.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Deja en el campo method el metodo y en key la key pasada por linea de comando
// Pre: self y argv no son NULL
int args_parser_get_method_and_key(args_parser_t* self, int argc, char** argv) {
  struct option arguments[] = {{"method", required_argument, 0, 'm'},
                               {"key", required_argument, 0, 'k'}};

  int cantidadCorrectas = 0;
  int opt = 0;

  while ((opt = getopt_long(argc, argv, "mk", arguments, NULL)) != -1) {
    if (opt == 'm') {
      strncpy(self->method, optarg, strlen(optarg) + 1);
      self->method[strlen(optarg)] = 0;
      cantidadCorrectas++;
    } else if (opt == 'k') {
      strncpy(self->key, optarg, strlen(optarg) + 1);
      self->key[strlen(optarg)] = 0;
      cantidadCorrectas++;
    } else {
      printf("Error. Se debe recibir en formato --method=<Method> --key=<Key>");
    }
  }

  return cantidadCorrectas != 2;
}
