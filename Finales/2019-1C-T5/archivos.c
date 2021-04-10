#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void read_reversed(FILE* file, size_t* read_seek, char buf[4]){

  fseek(file, *read_seek, SEEK_SET);
  int read = fread(buf, 4, 1, file);
  (*read_seek) -= (4 * read);
}

void createPadding(char buf[5], int amountOfZeros){
  for(int i = 0; i < amountOfZeros; i++){
    buf[i] = '0';
  }
}

int write_reversed(FILE* file, size_t* write_seek, char* decimal){


  if(strlen(decimal) < 4){
    char buf[5] = {0};
    createPadding(buf, 4 - strlen(decimal));
    (*write_seek) -= 4;
    fseek(file, (*write_seek), SEEK_SET);
    fwrite(buf, strlen(buf), 1, file);
    fwrite(decimal, strlen(decimal), 1, file);
    return 4;
  }
  else{
    (*write_seek) -= strlen(decimal);
    fseek(file, (*write_seek), SEEK_SET);
    fwrite(decimal, strlen(decimal), 1, file);
    return strlen(decimal);
  }

}

size_t getNewFileLength(FILE* file){

  if(!file)
    return 0;

    size_t fileLength = 0;
  while(!feof(file)){
    char buf[4] = {0};  // Voy leyendo el archivo de a 4 bytes

    int read = fread(buf, 4, 1, file);  // Dejo en el buffer los 4 bytes leidos.
    if(!read)
      break;

    int decimal;
    sscanf(decimal, "%4x", buf);  // No recuerdo a la perfeccion el orden de los parametros, pero estoy casi seguro que era asi, me deja en la variable decimal la representacion en decimal del buffer
    char hexa[12] = {0}; // Con 12 bytes puedo representar en decimal cualquier hexa de 4
    sprintf(decimal, "%4x", hexa); // Otra vez, no recuerdo el orden de los parametros.
    if(strlen(hexa) < 4)    // Si no llego a los 4 bytes, voy a agregar padding de 0s a izquierda, que no modifican el numero
      fileLength += 4;
    else
      fileLength += strlen(hexa);
  }

  return fileLength;
}


int main(){

  FILE* file = fopen("numeros.txt", "r+");
  if(!file)
    return 1;

  size_t fileLength = getNewFileLength(file);

  fseek(file, 0, SEEK_END);
  size_t read_seek = ftell(file);
  fseek(file, 0, SEEK_SET);

  size_t write_seek = fileLength;

  int bytesWritten = 0;

  while(bytesWritten < fileLength){

    char buf[4] = {0};
    read_reversed(file, &read_seek, buf);
    int decimal;
    sscanf(buf, "%4x", &decimal);  // No recuerdo a la perfeccion el orden de los parametros, pero estoy casi seguro que era asi, me deja en la variable decimal la representacion en decimal del buffer
    char hexa[12] = {0}; // Con 12 bytes puedo representar en decimal cualquier hexa de 4
    sprintf(hexa, "%d", decimal); // Otra vez, no recuerdo el orden de los parametros.
    bytesWritten += write_reversed(file, &write_seek, stringDecimal);


  }
}
