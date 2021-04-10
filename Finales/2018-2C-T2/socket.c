#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void printBuf(char* buf, int inserted){

  for(int i = 0; i < inserted; i++){
    printf("%c", buf[i]);
  }
  printf("\n");
  return;
}

int main(){

  char* port = "8080";

  struct addrinfo* serv_info;
  struct addrinfo hints;
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;

  getaddrinfo("localhost", port, &hints, &serv_info);

  int serverFD = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);
  bind(serverFD, serv_info->ai_addr, serv_info->ai_addrlen);
  listen(serverFD, 10);
  freeaddrinfo(serv_info);

  int clientFD = accept(serverFD, NULL, NULL);

  int connected = 1;

  char buf[41] = {0};
  int inserted = 0;

  printf("Connection accepted \n");

  while(connected){

    char character;
    int received = recv(clientFD, &character, sizeof(character), 0);
    if(!received){
      connected = 0;
      break;
    }

    if(character == '>' && inserted == 1){
      connected = 0;
      break;
    }else if(character == '>'){
      buf[inserted] = character;
      inserted++;
      printBuf(buf, inserted);
      inserted = 0;
    }else{
      buf[inserted] = character;
      inserted++;
    }
    }

  shutdown(clientFD, SHUT_RDWR);
  shutdown(serverFD, SHUT_RDWR);
  close(clientFD);
  close(serverFD);
}
