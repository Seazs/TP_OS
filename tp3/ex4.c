#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    char input[100];

    while (1) {
        printf("Entrez une commande (ou appuyez sur Ctrl+D pour terminer) : ");

        // Lire une ligne depuis stdin
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // L'utilisateur a appuyé sur Ctrl+D, terminer le programme
            printf("C’est la fin des haricots !\n");
            break;
        }

        // Supprimer le caractère de nouvelle ligne à la fin de l'entrée
        input[strcspn(input, "\n")] = 0;

        // Créer un processus enfant
        pid_t pid = fork();

        if (pid == -1) {
            perror("Erreur lors de la création du processus enfant");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Code du processus enfant
            // Exécuter la commande dans le processus fils
            execlp(input, input, (char *)NULL);
            // Si execlp échoue, afficher un message d'erreur
            perror("Erreur lors de l'exécution de la commande");
            exit(EXIT_FAILURE);
        } else {
            // Code du processus parent
            // Attendre que le processus enfant se termine
            wait(NULL);
        }
    }

    return 0;
}

