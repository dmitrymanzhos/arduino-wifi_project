CC = gcc
CFLAGS = -luv

all: udp-server

main: udp-server.o functions1.o
	$(CC) $? -o build/udp-server $(CFLAGS)

udp-server.o: udp-server.c 
	$(CC) $? -c $(CFLAGS)

functions1.o: functions1.c
	$(CC) $? -c $(CFLAGS)