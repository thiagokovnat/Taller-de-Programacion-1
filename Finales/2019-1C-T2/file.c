#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void read_reversed(FILE* file, size_t* read_seek, char buf[4]){

  fseek(file, (*read_seek), SEEK_SET);
  fread(buf, sizeof(char) * 4, 1, file);
  (*read_seek) -= (sizeof(char) * 4);
}

int write_reversed(FILE* file, size_t* write_seek, char* buf){

  char newBuf[4] = {0};
  if(strlen(buf) < 4){
    for(int i = 0; i < (4-strlen(buf)); i++){
      newBuf[i] = '0';
      printf("Adding Zeros \n");
    }

    fseek(file, (*write_seek), SEEK_SET);
    fwrite(newBuf, strlen(newBuf), 1, file);
    (*write_seek) += strlen(newBuf);
  }

  fseek(file, (*write_seek), SEEK_SET);
  fwrite(buf, strlen(buf), 1, file);

  if(strlen(buf) < 4){
    (*write_seek) -= strlen(newBuf);
    return 4;
  }else
    return strlen(buf);

}

int main(){

  FILE* file = fopen("numeros.txt", "r+");
  if(!file)
    return 1;

  // Procesar el largo del nuevo archivo

  int bytesRead = 0;
  int newFileLength = 0;
  while(!feof(file)){
    char hexa[4];
    int bytes = fread(hexa, sizeof(hexa), 1, file);
    if(!bytes)
      break;
    bytesRead += bytes * sizeof(hexa);
    int decimal;
    sscanf(hexa, "%4x", &decimal);
    char str[12] = {0};
    sprintf(str, "%d", decimal);
    if(strlen(str) < 4){
      newFileLength += 4;
    }else{
      newFileLength += strlen(str);
    }
    printf("Number read: %d , in string form: %s \n", decimal, str);
  }

  size_t read_seek = bytesRead - (4 * sizeof(char));
  size_t write_seek = newFileLength;
  int bytesWritten = 0;

  while(bytesWritten < newFileLength){
    char hexa[4] = {0};
    read_reversed(file, &read_seek, hexa);
    int decimal;
    sscanf(hexa, "%4x", &decimal);
    char str[12] = {0};
    sprintf(str, "%d", decimal);
    printf("IT 2: Number read: %d , in string form: %s \n", decimal, str);
    if(strlen(str) < 4){
      write_seek -= 4;
    }else{
      write_seek -= strlen(str);
    }
    int written = write_reversed(file, &write_seek, str);
    bytesWritten += written;
  }


  printf("Original file size in bytes: %i, File length after conversion: %i \n", bytesRead, newFileLength);
  fclose(file);
  return 0;
}
