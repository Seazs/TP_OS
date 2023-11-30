#include <pthread.h>
#include <stdio.h>

void *afficher1(void *ptr) {
  for (int i = 0; i < 100; i++) {
    printf("1\n");
  }
  return NULL;
}

void *afficher2(void *ptr) {
  for (int i = 0; i < 100; i++) {
    printf("2\n");
  }
  return NULL;
}

int main(int argc, char const *argv[]) {
  pthread_t tid;
  pthread_create(&tid, NULL, afficher1, NULL);
  afficher2(NULL);
  pthread_join(tid, NULL);
  return 0;
}
