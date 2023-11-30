#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Permet de définir un gestionnaire de signaux pour SIGPIPE,
// ce qui évite une fermeture abrupte du programme à la réception
// du signal (utile si vous avez des opérations de nettoyage à
// faire avant de terminer le programme)
#include <signal.h>

#include "../common.h"

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
  int longueur, i, ret;
  
  if (fgets(buffer, 1024, stdin) != NULL) {
     longueur = strlen(buffer) + 1;
     printf("Envoi...\n");
     checked_wr(write(sock, buffer, strlen(buffer) + 1));
     
     // Pour rappel, nous utilisons des sockets en mode
     // SOCK_STREAM. Par conséquent, il n'y a pas de
     // garanties sur le fait qu'un message implique
     // exactement une réception (plusieurs pourraient
     // être nécessaires). Il faut donc boucler sur read().
     i = 0;
     while (i < longueur) {
        ret = read(sock, buffer, longueur - i);
        if (ret <= 0) {
           if (ret < 0)
              perror("read");
           else
              printf("Déconnexion du serveur.\n");
           return 1;
        }
        
        i += ret;
     }
     
     printf("Recu : %s\n", buffer);
  }
  
  close(sock);
  return 0;
}
