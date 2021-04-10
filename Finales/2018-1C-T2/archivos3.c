#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>


void gen_file(){
  FILE* file = fopen("sumayor.dat", "wb");
  int8_t nums[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

  for(int i = 0; i < 20; i++){
    printf("Writing number: %d \n", nums[i]);
    fwrite(&nums[i], sizeof(int8_t), 1, file);
  }

  fclose(file);
}

int read_file(FILE* file, size_t* read_seek, int8_t* a){
  fseek(file, *read_seek, SEEK_SET);
  int read = fread(a, sizeof(int8_t), 1, file);
  if(!read)
    return 0;

  printf("Reading: %i \n", *a);
  (*read_seek) +=  (sizeof(int8_t));
  return 1;

}

int write_file(FILE* file, size_t* write_seek, int8_t* num){
  fseek(file, *write_seek, SEEK_SET);
  printf("Appending: %i \n", *num);
  int written = fwrite(num, sizeof(int8_t), 1, file);
  (*write_seek) += ((written == 1) * sizeof(int8_t));

  return ((written == 1) * sizeof(int8_t));
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


  FILE* file = fopen("sumayor.dat", "r+b");

  fseek(file, 0, SEEK_END);
  size_t write_seek = ftell(file);
  size_t endOriginal = write_seek;
  size_t read_seek = 0;

  int reading = 1;
  int written = 0;

  while(reading){
    int8_t a, b;

    if(read_file(file, &read_seek, &a) && read_file(file, &read_seek, &b)){
      int8_t sum = a+b;
      int8_t resta = a-b;
      int8_t or = a || b;


      written += write_file(file, &write_seek, &sum);
      written += write_file(file, &write_seek, &resta);
      written += write_file(file, &write_seek, &or);
    }else{
      reading = 0;
    }

    if(read_seek >= endOriginal)
      reading = 0;
  }

  written = 0;
  read_seek = endOriginal;
  write_seek = 0;
  reading = 1;

  printf("Shifting file...\n");

  while(reading){
    int8_t a;

    if(read_file(file, &read_seek, &a)){
      written += write_file(file, &write_seek, &a);
    }else{
      reading = 0;
    }
  }

  truncate("sumayor.dat", written);

  print_file(file);
  fclose(file);
}
