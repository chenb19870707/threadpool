.PHONY:clean all
CC=g++
CFLAGS=-Wall -g
BIN=echosvr echoclient echosvr2 p2psvr p2pcli
all:$(BIN)
%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -f *.o $(BIN)
