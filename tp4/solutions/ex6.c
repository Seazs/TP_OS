#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE 100000
#define N_THREADS 10

typedef struct {
  int* tableau;
  size_t taille;
  int somme;
} thread_args_t;

void remplir_tableau(int* tableau, size_t taille, int min, int max) {
  const int diff = max - min;
  for (int i = 0; i < taille; i++) {
    tableau[i] = min + (rand() % diff);
  }
}

void* somme(void* ptr) {
  thread_args_t* args = (thread_args_t*)ptr;
  int somme = 0;
  for (int i = 0; i < args->taille; i++) {
    somme += args->tableau[i];
  }
  args->somme = somme;
  return NULL;
}

int main(int argc, char const* argv[]) {
  // Initialiser la seed au timestamp actuel (en secondes)
  srand(time(NULL));
  int tab[TAILLE];
  remplir_tableau(tab, TAILLE, 0, 100);
  pthread_t tids[N_THREADS];
  thread_args_t args[N_THREADS];
  const size_t nb_elem_par_thread = TAILLE / N_THREADS;
  int* ptr = tab;
  for (int i = 0; i < N_THREADS; i++) {
    args[i].tableau = ptr;
    args[i].taille = nb_elem_par_thread;
    // Le nombre de threads peut ne pas être un multiple de la taille du tableau
    // On va donc ajouter au dernier threads les éléments "qui restent"
    if (i == N_THREADS - 1) {
      args[i].taille += TAILLE % N_THREADS;
    }
    pthread_create(&tids[i], NULL, somme, &args[i]);
  }

  int somme = 0.;
  for (int i = 0; i < N_THREADS; i++) {
    pthread_join(tids[i], NULL);
    somme += args[i].somme;
  }
  float moyenne = (float)somme / (float)TAILLE;
  printf("Moyenne du tableau: %f\n", moyenne);

  return 0;
}
