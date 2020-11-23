#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_args_parser.h"
#include "server_commands.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Server format: ./server port --method=<Method> --key=<Key>\n");
    return 0;
  }

  server_t server;
  if (server_create(&server, argv[1])) {
    printf("There was an error creating the server\n");
    return 0;
  }

  args_parser_t parser;
  if (args_parser_get_method_and_key(&parser, argc, argv)) {
    printf(
        "Argument error. Server format: ./server port --method=<Method> "
        "--key=<Key>\n");
    server_close(&server);
    return 0;
  }

  if (strcmp(parser.method, "rc4") == 0) {
    server_rc4(&server, parser.key);
  }

  else if (strcmp(parser.method, "cesar") == 0) {
    char* ptr;
    int ret = (int)strtol(parser.key, &ptr, 10);
    server_cesar(&server, ret);
  }

  else if (strcmp(parser.method, "vigenere") == 0) {
    server_vigenere(&server, parser.key);
  } else {
    printf("Metodo no reconocido.\n");
  }

  server_close(&server);
  return 0;
}
