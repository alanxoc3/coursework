# Netty-RPS
CLINKS = -lm
SLINKS = -pthread

client.out: client.o
	gcc $^ -o $@ $(CLINKS)

server.out: server.o
	gcc $^ -o $@ $(SLINKS)

# -------------------------------

client.o: src/client.c src/client.h
	gcc -c -o $@ $<

server.o: src/server.c src/server.h
	gcc -c -o $@ $<

clean:
	rm *.out *.o

all: client.out server.out
