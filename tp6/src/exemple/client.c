// Client side C/C++ program to demonstrate Socket programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../common.h"

int main() {
  int sock = checked(socket(AF_INET, SOCK_STREAM, 0));

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  // Conversion de string vers IPv4 ou IPv6 en binaire
  inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

  connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  char message[] = "Salut, ici le client !";
  size_t len = strlen(message);
  // On envoie jusqu'à len + 1 pour inclure le '\0' qui termine les chaînes de caractère
  write(sock, message, len + 1);
  close(sock);
  return 0;
}
