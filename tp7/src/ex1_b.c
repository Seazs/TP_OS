#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

typedef struct{
  int value;
  pthread_mutex_t mutex;
} CompteurSynchronise;

void* fonction_qui_compte_beaucoup(void* args){ 
  CompteurSynchronise* compteur = (CompteurSynchronise*)args;
  int i;
  for (i = 0; i<1000000; i++){
    pthread_mutex_lock(&compteur->mutex);
    compteur->value++;
    pthread_mutex_unlock(&compteur->mutex);
  }
  return NULL;
}

int main(int argc, char const* argv[]) {

  CompteurSynchronise compteur = {
    .value = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER
  };
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, fonction_qui_compte_beaucoup, &compteur );
  pthread_create(&thread2, NULL, fonction_qui_compte_beaucoup, &compteur);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL); 

  // A compléter
  printf("valeur du compteur: %i\n", compteur.value);
  return 0;
}
