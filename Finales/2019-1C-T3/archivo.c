#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 40

int read_file(FILE* file, int* read_seek, char* buf, size_t buf_length){
  fseek(file, (*read_seek), SEEK_SET);
  int bytesRead = getline(&buf, &buf_length, file);
  printf("Leido: %s \n", buf);
  (*read_seek) = ftell(file);
  return bytesRead;
}

int write_file(FILE* file, int* write_seek, char* line){
  fseek(file, (*write_seek), SEEK_SET);
  fwrite(line, strlen(line), 1, file);

  int written = strlen(line);
  if(line[strlen(line) - 1] != '\n'){
    char a = ' ';
    fwrite(&a, 1, 1, file);
    written++;
  }

  (*write_seek) += written;

  return written;
}

int main(){

  FILE* file = fopen("lineas.txt", "r+");

  char line[MAX_LINE] = {0};
  int read_seek = 0;
  int write_seek = 0;
  int length = MAX_LINE;

  int bytesRead = 0;
  int bytesWritten = 0;
  int bytes = 0;

  fseek(file, 0, SEEK_END);
  int fileLength = ftell(file);
  rewind(file);

  while(bytesRead < fileLength){

    bytes = read_file(file, &read_seek, line, length);
    if(bytes == -1){
      break;
    }

    bytesRead += bytes;
    char* token = strtok(line, " ");
    while(token != NULL){
      printf("Processing Word: %s \n", token);
      if(strlen(token) > 3)
        bytesWritten += write_file(file, &write_seek, token);
      token = strtok(NULL, " ");
    }

  }

  truncate("lineas.txt", bytesWritten);
  fclose(file);
}
