#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 30

void printSumatoria(char* buf, int bytesReceived){

  int sumatoria = 0;
  int i = 0;
  while(i < bytesReceived){
    char num[4] = {0};
    int index = 0;

    while((buf[i] != '+') && (buf[i] != '=') && (i < bytesReceived)){
      num[index] = buf[i];
      index++;
      i++;
    }

    int numero = atoi(num);
    printf("RECEIVED NUM: %i \n", numero);
    sumatoria += numero;
    i++;
  }

  printf("La sumatoria es: %i \n", sumatoria);
}
int main(int argc, char** argv){

  char* port = argv[1];

  struct addrinfo* serv_info;
  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family= AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;

  getaddrinfo("localhost", port, &hints, &serv_info);

  int serverFD = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);
  int val = 1;
  setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  bind(serverFD, serv_info->ai_addr, serv_info->ai_addrlen);
  listen(serverFD, 10);
  freeaddrinfo(serv_info);

  int clientFD = accept(serverFD, NULL, NULL);
  printf("Connection established! \n");


  int connected = 1;

  while(connected){
    char message[MAX_LEN] = {0};
    int bytesReceived = 0;
    while(bytesReceived < MAX_LEN - 1){
      char character;
      int received = recv(clientFD, &character, sizeof(char), 0);
      if(character == '='){
        message[bytesReceived] = character;
        bytesReceived++;
        break;
      }else if(character == ' '){ // NC Debug Only
        continue;
      }else{
        message[bytesReceived] = character;
        bytesReceived += 1;
      }
    }

    if(bytesReceived <= 1){
      connected = 0;
    }else{
      printSumatoria(message, bytesReceived);
    }
  }

  shutdown(clientFD, SHUT_RDWR);
  shutdown(serverFD, SHUT_RDWR);
  close(clientFD);
  close(serverFD);
}
