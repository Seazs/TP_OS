// Server side C/C++ program to demonstrate Socket programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../common.h"

int main(int argc, char const *argv[]) {
  // Creating socket file descriptor
  int server_fd = checked(socket(AF_INET, SOCK_STREAM, 0));

  int opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  bind(server_fd, (struct sockaddr *)&address, sizeof(address));
  listen(server_fd, 3);

  size_t addrlen = sizeof(address);
  int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
  char buffer[1024];
  read(new_socket, buffer, 1024);
  printf("Message reçu:%s\n", buffer);

  // On renvoie le message reçu
  write(new_socket, buffer, strlen(buffer) + 1);

  close(server_fd);
  close(new_socket);
  return 0;
}