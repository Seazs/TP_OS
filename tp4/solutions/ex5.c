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
  for (int i = 0; i < 10; i++) {
    sleep(rand() % 3 + 1);
    printf("%s est arrive a la %dieme balise\n", cheval->nom, i);
  }
  printf("%s a fini la course !\n", cheval->nom);
  return NULL;
}

int main(int argc, char const* argv[]) {
  srand(time(NULL));
  cheval_t henry;
  henry.nom = "Henry";
  henry.numero = 14;

  cheval_t jacques;
  jacques.nom = "Jacques";
  jacques.numero = 20;

  pthread_t t1, t2;
  pthread_create(&t1, NULL, course, &henry);
  pthread_create(&t2, NULL, course, &jacques);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("La cours est terminee\n");
  return 0;
}
