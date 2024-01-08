#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  char code_super_secret[] = "le code secret";
  const char salutations[0];
  for (int i = 0; i < sizeof(salutations) + sizeof(code_super_secret); i++) {
    printf("%c", salutations[i]);
  }
  return 0;
}
