#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

atomic_int count = 0;

void* incrementer(void* ptr) {
  for (int i = 0; i < 500000; i++) {
    count++;
  }
  return NULL;
}

int main() {
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, incrementer, NULL);
  pthread_create(&tid2, NULL, incrementer, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  printf("Count = %d\n", count);
  return 0;
}
