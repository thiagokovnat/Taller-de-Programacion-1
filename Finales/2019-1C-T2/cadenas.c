#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char** argv){

  char* frase = argv[1];
  char* palabra = argv[2];

  int newLength = 0;

  char* token = strtok(frase, " ");

  while(token != NULL){
    if(strcmp(token, palabra) == 0){
      printf("%s ", token);
      printf("%s ", token);
    }
    else{
      printf("%s ", token);
    }

    token = strtok(NULL, " ");
  }
  printf("\n");

}
