#include <stdlib.h>
int main(void) {
	char* p = malloc(20);
	char *q = malloc(20);
	free(p);
	return 0;
}
