#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int read_file(FILE* file, char* buf, int bufsize, size_t* read_seek){

  fseek(file, (*read_seek), SEEK_SET);
  int read = getline(&buf, (size_t*)&bufsize, file);
  (*read_seek) += read;

  return read;
}

int isDelim(char character){
  return (character == ' ' || character == '_' || character == '_' || character == '.' || character == ';' || character == ':' || character == '\n' || character == '?');
}

int hasToBeEliminated(char* buf){

  char prevCharacter = ' ';
  char character = 'a';

  int i = 0;
  int amountOfWords = 0;
  while(i < strlen(buf)){
    character = buf[i];
    if(isDelim(prevCharacter) && !isDelim(character)){
      amountOfWords++;
    }

    prevCharacter = character;
    i++;
  }

  return amountOfWords <= 1;
}

int write_file(FILE* file, char* buf, size_t* write_seek){

  fseek(file, (*write_seek), SEEK_SET);
  printf("Writing buf: %s \n", buf);
  int written = fwrite(buf, strlen(buf), 1, file);
  (*write_seek) += (written * strlen(buf));

  return (written * strlen(buf));
}

int main(){

  FILE* file = fopen("texto.txt", "r+");
  size_t read_seek = 0;
  size_t write_seek = 0;
  int continuar= 1;
  int bytes_written = 0;

  while(continuar){
    char buf[40] = {0};
    int size = 40;

    if(read_file(file, buf, size, &read_seek) == -1){
      continuar = 0;
      break;
    }


    if(!hasToBeEliminated(buf))
      bytes_written += write_file(file, buf, &write_seek);

  }

  truncate("texto.txt", bytes_written);
  fclose(file);
}
