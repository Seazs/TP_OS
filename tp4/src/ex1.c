#include <pthread.h>
#include <stdio.h>

void *write_hundred_time1(void *number) {
  int *number_ptr = (int *)number;
  int number_value = *number_ptr;
  for (int i = 0; i < 100; i++) {
    printf("%d", number_value);
  }
  return NULL;
}


void *write_hundred_time2(void *number) {
  int *number_ptr = (int *)number;
  int number_value = *number_ptr;
  for (int i = 0; i < 100; i++) {
    printf("%d", number_value);
  }
  return NULL;
}

int main(int argc, char const *argv[]) {
  pthread_t first; 
  
  int first_number = 1;
  int second_number = 2;

  pthread_create(&first, NULL, write_hundred_time1, &first_number);
  write_hundred_time2(&second_number);

  pthread_join(first, NULL);
  printf("\n");
  return 0;
}
