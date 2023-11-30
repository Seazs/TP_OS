#include <pthread.h>
#include <stdio.h>

void *increment(void *count) {
  int *count_ptr = (int *)count;
  
  for (int i = 0; i < 5000000; i++) {
    *count_ptr = *count_ptr + 1;
  }
  return NULL;
}

int main(int argc, char const *argv[]) {
  int count = 0;
  
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, increment, &count);
  pthread_create(&thread2, NULL, increment, &count);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("Count = %d\n", count);
  return 0;
}
