#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define MAX_LENGTH 10

int finished(char* buf){
  char* keyword = "FINAL";
  return (strcmp(buf, keyword) == 0);
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
    char buf[MAX_LENGTH] = {0};
    int bytesReceived = 0;
    while(bytesReceived < MAX_LENGTH - 1){
      char character;
      int received = recv(clientFD, &character, sizeof(char), 0);
      printf("Received %i bytes in char: %c \n", received, character);
      if(character == ' '){
        break;
      }else if(character == 0){
        continue;
      }else{
        buf[bytesReceived] = character;
        bytesReceived += received;
      }
    }
    if(finished(buf)){
      connected = 0;
    }else{
      printf("%s \n", buf);
    }
  }


  shutdown(clientFD, SHUT_RDWR);
  shutdown(serverFD, SHUT_RDWR);
  close(clientFD);
  close(serverFD);
}
