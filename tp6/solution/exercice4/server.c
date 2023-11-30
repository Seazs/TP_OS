#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

// Permet de définir un gestionnaire de signaux pour SIGPIPE,
// ce qui évite une fermeture abrupte du programme à la réception
// du signal (utile si vous avez des opérations de nettoyage à
// faire avant de terminer le programme)
#include <signal.h>

#include "../common.h"

bool lire_exactement(int fd, char* buffer, int size);

int main(void) {
  // Permet que write() retourne 0 en cas de réception
  // du signal SIGPIPE.
  signal(SIGPIPE, SIG_IGN);
  
  int server_fd = checked(socket(AF_INET, SOCK_STREAM, 0));

  int opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
  
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  checked(bind(server_fd, (struct sockaddr *)&address, sizeof(address)));
  checked(listen(server_fd, 3));

  size_t addrlen = sizeof(address);
  int new_socket = checked(accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen));
  
  char buffer[1024];
  uint32_t taille = 0;
  
  while (lire_exactement(new_socket, (char*)&taille, 4) /* lire la taille du message */
      && lire_exactement(new_socket, buffer, ntohl(taille))) { /* lire le message */
      
      checked_wr(write(new_socket, buffer, ntohl(taille)));
  }
  
  close(server_fd);
  close(new_socket);
  return 0;
}

bool lire_exactement(int fd, char* buffer, int size) {
   int lu, i = 0;
   while (i < size && (lu = read(fd, buffer, size - i)) > 0) {
      i += lu;
   }
   
   if (lu < 0) {
      perror("read()");
   }
   
   return lu > 0;
}