#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

typedef struct {
   int valeur;
   pthread_mutex_t mutex;
} CompteurSynchronise;

void* fonction_qui_compte_beaucoup(void* args) {
   CompteurSynchronise* compteur = (CompteurSynchronise*)args;
   
   for (int i = 0; i < 100000; ++i) {
      pthread_mutex_lock(&compteur->mutex);
      ++compteur->valeur;
      pthread_mutex_unlock(&compteur->mutex);
   }
   return NULL;
}

int main(void) {
  pthread_t threads[2];
  CompteurSynchronise compteur = {
     .valeur = 0,
     .mutex = PTHREAD_MUTEX_INITIALIZER
  };
  
  pthread_create(&threads[0], NULL, fonction_qui_compte_beaucoup, &compteur);
  pthread_create(&threads[1], NULL, fonction_qui_compte_beaucoup, &compteur);
  
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  
  printf("Valeur finale du compteur : %d.\n", compteur.valeur);
  return 0;
}
