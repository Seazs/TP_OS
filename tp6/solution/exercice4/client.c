#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
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
  int sock = checked(socket(AF_INET, SOCK_STREAM, 0));

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  // Conversion de string vers IPv4 ou IPv6 en binaire
  inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

  checked(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)));
  
  char buffer[1024];
  uint32_t longueur;
  
  while (fgets(buffer, 1024, stdin) != NULL) {
     longueur = strlen(buffer) + 1;
     printf("Envoi...\n");
     
     // Comme on envoie sur le réseau une valeur
     // binaire encodée sur plusieurs octets, il
     // faut faire attention au boutisme.
     // Nous utilisons la technique standard pour
     // ça : l'envoi converti en big-endian (htonl())
     // et la réception converti du big-endian vers
     // le boutisme local (ntohl())
     longueur = htonl(longueur);
     checked_wr(write(sock, &longueur, 4));
     
     longueur = ntohl(longueur);
     checked_wr(write(sock, buffer, longueur));
     
     if (!lire_exactement(sock, buffer, longueur)) {
        return 1;
     }
     
     printf("Recu : %s\n", buffer);
  }
  
  close(sock);
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
