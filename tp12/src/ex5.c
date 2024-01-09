#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int nouveau_std = open("stdout.txt", O_CREAT | O_WRONLY, 0644);
  if(nouveau_std == -1) {
    perror("open(stdout.txt)");
    return 1;
  }

  if(dup2(nouveau_std, STDOUT_FILENO) == -1) {
    perror("dup2(stdout.txt)");
    return 1;
  }

  pid_t fils = fork();

  if (fils == 0) {
  } else if (fils > 0) {
    execlp("ls", "ls", NULL);
  } else {
    perror("fork()");
    return 1;
  }

  close(nouveau_std);


  return 0;
}
