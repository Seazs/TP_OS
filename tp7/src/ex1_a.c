#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdatomic.h>

atomic_int count = 0;

void* fonction_qui_compte_beaucoup(void* args) { 
  for (int i = 0; i < 1000000; i++) {
    count++;
  }
  return NULL; }

int main(int argc, char const* argv[]) {

  
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, fonction_qui_compte_beaucoup, NULL);
  pthread_create(&thread2, NULL, fonction_qui_compte_beaucoup, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL); 

  printf("Valeur finale du compteur : %d.\n", count);
  // A compléter
  return 0;
}
