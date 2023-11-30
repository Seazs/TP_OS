CFLAGS += -Wall -Wextra -pedantic -O0 -std=gnu17
all: ex1_client ex3_client ex4_client ex1_server ex3_server ex4_server

ex1_client: exercice1/echo_client.c common.h
	${CC} -o $@ $^ ${CFLAGS}

ex1_server: exercice1/echo_server.c common.h
	${CC} -o $@ $^ ${CFLAGS}

ex3_client: exercice3/echo_client.c common.h
	${CC} -o $@ $^ ${CFLAGS}

ex3_server: exercice3/echo_server.c common.h
	${CC} -o $@ $^ ${CFLAGS}

ex4_client: exercice4/client.c common.h
	${CC} -o $@ $^ ${CFLAGS}

ex4_server: exercice4/server.c common.h
	${CC} -o $@ $^ ${CFLAGS}

clean:
	-rm ex[134]_client ex[134]_server
