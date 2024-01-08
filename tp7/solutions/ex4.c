#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PRODUITS 10

typedef struct {
   int produits[MAX_PRODUITS];
   int size;
   sem_t sem_produits_dispo;
   sem_t sem_place_restante;
   pthread_mutex_t mtx_produits;
} Produit;

int pop(Produit* produits) {
   int retour = produits->produits[0];

   for (int i = 0; i < produits->size - 1; ++i) {
      produits->produits[i] = produits->produits[i + 1];
   }
   
   --produits->size;
   sem_post(&produits->sem_place_restante);
   
   return retour;
}

void push(Produit* produits, int valeur) {
    produits->produits[produits->size] = valeur;
    ++produits->size;
    
    sem_post(&produits->sem_produits_dispo);
}

void *producteur(void *args) {
   Produit* produits = (Produit*)args;
   
   while (1) {
      for (int i = rand() % 15 + 5; i >= 0; --i) {
         // On attend qu'il y ait de la place pour
         // la production
         sem_wait(&produits->sem_place_restante);
         
         // Accès exclusif aux produits pour éviter les
         // lectures et écritures concurrentes
         pthread_mutex_lock(&produits->mtx_produits);
         
         push(produits, rand() % 100);
         
         pthread_mutex_unlock(&produits->mtx_produits);
      }
      
      printf("Au dodo !\n");
      sleep(5);
   }
   
   return NULL;
}

void *consommateur(void *args) {
   Produit* produits = (Produit*)args;
 
   while (1) {
      // On attend qu'un produit soit disponible
      sem_wait(&produits->sem_produits_dispo);
      
      // Accès exclusif aux produits pour éviter les
      // lectures et écritures concurrente
      pthread_mutex_lock(&produits->mtx_produits);
      
      if (produits->size > 0) {
         printf("Lu : %d\n", pop(produits));
      }
      
      pthread_mutex_unlock(&produits->mtx_produits);
   }
   
   return NULL;
}

int main(void) {
  Produit produits;
  pthread_t th_producteur, th_consommateur;
  
  srand(time(NULL));
  
  produits.size = 0;
  pthread_mutex_init(&produits.mtx_produits, NULL);
  sem_init(&produits.sem_produits_dispo, 0, 0);
  sem_init(&produits.sem_place_restante, 0, MAX_PRODUITS);
  
  pthread_create(&th_producteur, NULL, producteur, &produits);
  pthread_create(&th_consommateur, NULL, consommateur, &produits);
  
  pthread_join(th_producteur, NULL);
  pthread_join(th_consommateur, NULL);
  
  return 0;
}
