.PHONY:clean all
CC=g++
CFLAGS=-Wall -g
BIN=echosvr echocli
all:$(BIN)
%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -f *.o $(BIN)
