#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client_commands.h"
#include "common_args_parser.h"
#define CLIENT_ARG_HOST 1
#define CLIENT_ARG_PORT 2

int main(int argc, char** argv) {
  if (argc < 5) {
    printf("Format Error. Client format: ./client host port --method --key");
    return 0;
  }

  client_t client;
  args_parser_t parser;
  if (client_create(&client, argv[CLIENT_ARG_HOST], argv[CLIENT_ARG_PORT])) {
    return 0;
  }

  args_parser_get_method_and_key(&parser, argc, argv);

  if (strcmp(parser.method, "rc4") == 0) {
    client_rc4(&client, parser.key);
  }

  else if (strcmp(parser.method, "cesar") == 0) {
    char* ptr;
    int ret = (int)strtol(parser.key, &ptr, 10);
    client_cesar(&client, ret);
  }

  else if (strcmp(parser.method, "vigenere") == 0) {
    client_vigenere(&client, parser.key);
  } else {
    printf("Metodo no reconocido.\n");
  }

  client_close(&client);
}
