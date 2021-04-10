#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printSum(char* buf, int inserted){



  int index = 0;
  int i = 0;
  int number;
  int sum = 0;

  while(i < inserted){
    char num[4] = {0};

    while(buf[i] != '+' && i < inserted){
      num[index] = buf[i];
      i++;
      index++;
    }

    number = atoi(num);
    sum += number;
    i++;
    index = 0;
  }

  printf("Total Sum of Package: %i \n", sum);

}
int main(int argc, char** argv){

  char* port = argv[1];

  struct addrinfo* serv_info;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;

  getaddrinfo("localhost", port, &hints, &serv_info);

  int serverFD = socket(serv_info->ai_family, serv_info->ai_socktype , serv_info->ai_protocol);
  bind(serverFD, serv_info->ai_addr, serv_info->ai_addrlen);
  freeaddrinfo(serv_info);
  listen(serverFD, 10);

  printf("Waiting for connection...\n");
  int clientFD = accept(serverFD, NULL, NULL);
  printf("Connection accepted...\n");
  char buf[40] = {0};
  char character = ' ';
  char prevCharacter = ' ';
  int inserted = 0;
  int connected = 1;

  while(connected){

    recv(clientFD, &character, sizeof(character), 0);

    if(character == '['){
      prevCharacter = character;
      continue;
    }
    else if(character == ']' && prevCharacter == '[')
      connected = 0;
    else if(character == ']'){
      printSum(buf, inserted);
      inserted = 0;
    }
    else if(character == ' ') //NC DEBUG ONLY
      continue;
    else{
      buf[inserted] = character;
      prevCharacter = character;
      inserted++;
    }

  }

  shutdown(clientFD, SHUT_RDWR);
  shutdown(serverFD, SHUT_RDWR);
  close(clientFD);
  close(serverFD);
}
