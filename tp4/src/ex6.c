#include <pthread.h>
#include <stdlib.h>

void remplir_tableau(int* tableau, size_t taille, int min, int max) {
  const int diff = max - min;
  for (int i = 0; i < taille; i++) {
    tableau[i] = min + (rand() % diff);
  }
}

int main(int argc, char const* argv[]) {
  // Initialiser la seed
  srand(0);

  return 0;
}
