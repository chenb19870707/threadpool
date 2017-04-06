.PHONY:clean all
CC=g++
CFLAGS=-Wall -g
BIN=echosvr echocli getip
all:$(BIN)
%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -f *.o $(BIN)
