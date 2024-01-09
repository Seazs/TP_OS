CC = gcc


all: datarace hacker leak listing6.1 memleak overflow return_local_pointer use_after_free ex2

ex2:
	$(CC) -o ex2 ex2.c

datarace:
	$(CC) -o datarace datarace.c -fsanitize=thread -g

hacker:
	$(CC) -o hacker hacker.c

leak:
	$(CC) -o leak leak.c -lpthread

listing6.1:
	$(CC) -o listing6.1 listing6.1.c

memleak:
	$(CC) -o memleak memleak.c -fsanitize=address -g 

overflow:
	$(CC)  -o overflow overflow.c -fsanitize=address -g 

return_local_pointer:
	$(CC) -o return_local_pointer return_local_pointer.c -fsanitize=address -g -Wall -Wextra

use_after_free:
	$(CC) -o use_after_free use_after_free.c -fsanitize=address -g 

clean:
	rm -f datarace hacker leak listing6.1 memleak overflow return_local_pointer use_after_free ex2