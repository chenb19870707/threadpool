.PHONY:clean all
CC=g++
CFLAGS=-Wall -g
BIN=echosvr echocli echocli2
all:$(BIN)
%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -f *.o $(BIN)
