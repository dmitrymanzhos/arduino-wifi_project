CC = gcc
CFLAGS = -luv

all: udp-server

udp-server: udp-server.o functions1.o
	$(CC) udp-server.o functions1.o -o udp-server $(CFLAGS)

udp-server.o: udp-server.c 
	$(CC) $? -c $(CFLAGS)

functions1.o: functions1.c
	$(CC) $? -c $(CFLAGS)