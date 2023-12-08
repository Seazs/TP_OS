#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct{
  int stock[10];
  sem_t sem;
} gestion_stock;

void *producteur(void *args) { 
  for (int i = 0; i < 9; i++) {
    
  }
  return NULL; }

void *consommateur(void *args) { return NULL; }

int main(int argc, char const *argv[]) {
  pthread_t thread1, thread2;
  gestion_stock stock;
  sem_init(&stock.sem, 0, 0);
  pthread_create(&thread1, NULL, producteur, &stock);
  pthread_create(&thread2, NULL, consommateur, &stock);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
