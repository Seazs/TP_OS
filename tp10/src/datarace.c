#include <pthread.h>
#include <stdbool.h>

static volatile bool flip1 = false;
static volatile bool flip2 = false;

void* th_flip(void* p) {
	(void)p;
	while (!flip1) {}
	flip2 = true;
	return NULL;
}

int main() {
	pthread_t th;
	pthread_create(&th, NULL, th_flip, NULL);
	flip1 = true;
	while (!flip2);
	pthread_join(th, NULL);
	return 0;
}
