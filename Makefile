CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src

all: server publisher subscriber

server: $(SRC)/server.c
	$(CC) $(CFLAGS) -o server $(SRC)/server.c

publisher: $(SRC)/publisher.c
	$(CC) $(CFLAGS) -o publisher $(SRC)/publisher.c

subscriber: $(SRC)/subscriber.c
	$(CC) $(CFLAGS) -o subscriber $(SRC)/subscriber.c

clean:
	rm -f server publisher subscriber
	rm -f /tmp/pubsub/*

.PHONY: all clean
