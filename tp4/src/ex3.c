#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

atomic_int count = 0;

void* increment(void *ptr) {
  
  for (int i = 0; i < 5000000; i++) {
    count++;
  }
  return NULL;
}


int main(int argc, char const *argv[]) {
  
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, increment, NULL);
  pthread_create(&thread2, NULL, increment, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("Count = %d\n", count);
  return 0;
}

