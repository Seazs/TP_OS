#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

const int taille = 4;
int sg = 0;
int ig;

int sum(int a, int b) {
  int sf = a + b;
  return sf;
}

int main(int argc, char const *argv[]) {
  ig = 100;
  for (int i = 0; i < taille; i++) {
    sg = sum(i, ig);
  }
  printf("sg = %d\n", sg);
  printf("adresse de taille: %p\n", &taille);
  printf("adresse de main: %p\n", &main);
  printf("adresse de sum: %p\n", &sum);
  printf("adresse de getpid: %p\n", &getpid);
  printf("adresse de printf: %p\n", &printf);

  char file[128];
  sprintf(file, "/proc/%d/maps", getpid());
  printf("Affichage du fichier %s\n", file);
  int fd = open(file, O_RDONLY);
  char buf[128];
  while (read(fd, buf, 128) > 0) {
    write(STDOUT_FILENO, buf, 128);
  }
  write(STDOUT_FILENO, "\n", 1);
  close(fd);
  return 0;
}
