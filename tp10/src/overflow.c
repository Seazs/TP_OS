#include <stdlib.h>

int main(void) {
   char *p = malloc(16);
   p[24] = 1;
   free(p);
   return 0;
}
