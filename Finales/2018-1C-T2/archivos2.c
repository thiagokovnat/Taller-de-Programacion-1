#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>


void gen_file(){
  FILE* file = fopen("multiplos6.dat", "wb");
  int8_t nums[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

  for(int i = 0; i < 20; i++){
    printf("Writing number: %d \n", nums[i]);
    fwrite(&nums[i], sizeof(int8_t), 1, file);
  }

  fclose(file);
}

int read_file(FILE* file, size_t* read_seek, int8_t* num){
  fseek(file, *read_seek, SEEK_SET);
  int read = fread(num, sizeof(int8_t), 1, file);
  (*read_seek) += ((read == 1) * sizeof(int8_t));
  return read == 1;
}

int write_file(FILE* file, size_t* write_seek, int8_t* num){
  fseek(file, *write_seek, SEEK_SET);
  int written = fwrite(num, sizeof(int8_t), 1, file);
  (*write_seek) += ((written == 1) * sizeof(int8_t));
  return written * sizeof(int8_t);
}

void print_file(FILE* file){
  fseek(file, 0, SEEK_SET);

  while(!feof(file)){
    int8_t num;
    int read = fread(&num, sizeof(int8_t), 1, file);
    if(!read)
      break;
    printf("Number: %i \n", num);
  }
}

int main(){

  gen_file();
  FILE* file = fopen("multiplos6.dat", "r+b");
  int reading = 1;
  size_t read_seek = 0;
  size_t write_seek = 0;
  int written = 0;
  while(reading){
    int8_t num;
    if(read_file(file, &read_seek, &num) == 1){
      if(num % 6 != 0){
        written += write_file(file, &write_seek, &num);
      }
    }else{
      reading = 0;
    }
  }

  truncate("multiplos6.dat", written);
  print_file(file);
  fclose(file);
  return 0;
}
