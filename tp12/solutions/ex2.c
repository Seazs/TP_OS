#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void) {
   pid_t fils = fork();

   if (fils == 0) {
      int nouveau_stdout = open("stdout.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (nouveau_stdout == -1) {
         perror("open()");
         return 1;
      }

      if (dup2(nouveau_stdout, 1) == -1) {
         perror("open()");
         return 1;
      }
      close(nouveau_stdout);

      execlp("ls", "ls", "-l", NULL);
      perror("execlp()");
      return 1;
   } else if (fils > 0) {
      wait(NULL);
      printf("Programme exécuté !\n");
   } else {
      perror("fork()");
      return 1;
   }

   return 0;
}
