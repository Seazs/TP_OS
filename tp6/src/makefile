folder=ex4

all: client server# exemple

exemple: exemple/client.c exemple/server.c
	gcc -o client_exemple exemple/client.c
	gcc -o server_exemple exemple/server.c

client: $(folder)/client.c common.h
	gcc -o client $(folder)/client.c common.h

server: $(folder)/server.c common.h 
	gcc -o server $(folder)/server.c common.h 
