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

    // lis l'entrée tant que l'utilisateur n'a pas appuyé sur ctrl+d
    char message[100];
    printf("Entrez un message : ");
    fgets(message, sizeof(message), stdin);
    while(!feof(stdin)){
        printf("message : %s\n", message);
        size_t len = strlen(message);
        //on envoie la taille du message
        write(sock, &len, sizeof(size_t));
        // On envoie jusqu'à len + 1 pour inclure le '\0' qui termine les chaînes de caractère
        write(sock, message, len + 1);

        printf("2\n");
        // On lit la réponse du serveur
        size_t len_retour;
        read(sock, &len_retour, sizeof(size_t));
        char buffer[len_retour];
        printf("3\n");
        read(sock, buffer, len_retour + 1);
        printf("4\n");
        printf("Message reçu : %s\n", buffer);
        printf("Entrez un message : ");
        fgets(message, sizeof(message), stdin);
    }

    write(sock, "fin", 4);
    
    close(sock);
    return 0;
}
