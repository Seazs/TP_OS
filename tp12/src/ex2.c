#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t fils = fork();

  if (fils == 0) {
  } else if (fils > 0) {
  } else {
    perror("fork()");
    return 1;
  }

  return 0;
}
