#include <stdlib.h>

void foo(char* p) {
   int i = 0;
   *p = i + 'x';
}

int main(void) {
   char *p = malloc(16);
   p[0] = 1;
   free(p);
   foo(p);
   return 0;
}
