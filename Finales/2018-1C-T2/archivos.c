#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>


void gen_file(){
  FILE* file = fopen("binary.dat", "wb");
  int32_t nums[10] = {0, 0 , 0xffffffff, 1, 1, 0xffffffff, 1, 2, 3, 0xffffffff};

  for(int i = 0; i < 10; i++){
    printf("Writing number: %d \n", nums[i]);
    int32_t bigendian = htonl(nums[i]);
    fwrite(&bigendian, sizeof(int32_t), 1, file);
  }

  fclose(file);
}

int32_t read_number(FILE* file, size_t* read_seek){

  int32_t num;
  fseek(file, *read_seek, SEEK_SET);
  int read = fread(&num, sizeof(int32_t), 1, file);
  if(read)
    (*read_seek) += sizeof(int32_t);
  else{
    printf("EOF REACHED \n");
    return 404;
  }

  printf("Read num: %d \n", ntohl(num));
  return ntohl(num);
}

int write_file(FILE* file, size_t* write_seek, int32_t num){

  fseek(file, *write_seek, SEEK_SET);
  int32_t bigendian = htonl(num);
  fwrite(&bigendian, sizeof(int32_t), 1, file);
  bigendian = 0xffffffff;
  bigendian = htonl(bigendian);
  fwrite(&bigendian, sizeof(int32_t), 1, file);

  (*write_seek) += (2 * sizeof(int32_t));

  return (2 * sizeof(int32_t));

}

void print_file(FILE* file){

  fseek(file, 0, SEEK_SET);
  while (!feof(file)) {
    int32_t num;
    int read = fread(&num, sizeof(int32_t), 1, file);
    if(!read)
      break;

    if(num == 0xffffffff)
      printf("END \n");
    else
      printf("%d \n", ntohl(num));
  }

}

int main(){


  gen_file();
  FILE* file = fopen("binary.dat", "r+b");
  if(!file)
  return 0;

  size_t read_seek = 0;
  size_t write_seek = 0;

  int32_t sumatoria = 0;
  int written = 0;
  while(!feof(file)){

    int32_t num = read_number(file, &read_seek);

    if(num == 404)
      break;

    if(num == 0xffffffff){
      written += write_file(file, &write_seek, sumatoria);
      sumatoria = 0;
    }else{
      sumatoria += num;
    }

  }

  truncate("binary.dat", written);

  print_file(file);

  fclose(file);
  return 0;
}
