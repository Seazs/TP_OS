#include <pthread.h>
#include <stdio.h>
void* incrementer(void* ptr) {
  int* count = (int*)ptr;
  for (int i = 0; i < 500000; i++) {
    *count = *count + 1;
  }
  return NULL;
}

int main(int argc, char const *argv[]) {
  int count = 0;
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, incrementer, &count);
  pthread_create(&tid2, NULL, incrementer, &count);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  printf("Count = %d\n", count);
  return 0;
}
