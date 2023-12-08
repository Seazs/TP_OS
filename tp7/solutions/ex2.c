#include <stdatomic.h>

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

void* fonction_qui_compte_beaucoup(void* args) {
   atomic_int* compteur = (atomic_int*)args;
   
   for (int i = 0; i < 100000; ++i) {
      ++*compteur;
   }
   return NULL;
}

int main(void) {
  atomic_int compteur = 0;
  
  pthread_t threads[2];
  
  
  pthread_create(&threads[0], NULL, fonction_qui_compte_beaucoup, &compteur);
  pthread_create(&threads[1], NULL, fonction_qui_compte_beaucoup, &compteur);
  
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  
  printf("Valeur finale du compteur : %d.\n", compteur);
  return 0;
}

