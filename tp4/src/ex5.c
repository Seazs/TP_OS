#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



typedef struct {
  char* nom;
  int numero;
} cheval_t;

void* course(void* ptr) {
  cheval_t* cheval = (cheval_t*)ptr;
  printf("Le cheval %s est sur le depart (numero %d)\n", cheval->nom, cheval->numero);
  for(int i = 0; i < 10; i++){
    int temps = rand() % 3 + 1;
    sleep(temps);
    printf("le cheval %s a atteint la balise %d\n", cheval->nom, i);
  }
  printf("Le cheval %s a termine la course\n", cheval->nom);
  // rand() génère un nombre aléatoire entre 0 et MAX_INT
  // sleep(<n_secondes>) permet d'endormir le thread pendant n secondes
  // TODO
  return NULL;
}

int main(int argc, char const* argv[]) {
  // Initialiser la 'seed' du module random
  srand(time(NULL));
  cheval_t henry;
  henry.nom = "Henry";
  henry.numero = 14;

  cheval_t alfred;
  alfred.nom = "Alfred";
  alfred.numero = 10;
  pthread_t t1, t2;
  pthread_create(&t1, NULL, course, &henry);
  pthread_create(&t2, NULL, course, &alfred);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("La cours est terminee\n");
  return 0;
}
