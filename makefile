all: client server
client.o: client.c
	gcc -c client.c
client: client.o
	gcc client.o -o client
server.o: server.c
	gcc -c server.c
server: server.o
	gcc server.o -o server

clean:
	rm -f server.o client.o server client
