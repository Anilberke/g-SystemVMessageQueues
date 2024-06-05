CC = gcc
CFLAGS = -Wall

CLIENT_SRC = client.c
SERVER_SRC = server.c
READ_SRC = read.c
WRITE_SRC = write.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
READ_OBJ = $(READ_SRC:.c=.o)
WRITE_OBJ = $(WRITE_SRC:.c=.o)

all: client server read_process write_process

client: $(CLIENT_OBJ)
	$(CC) -o client $(CLIENT_OBJ)

server: $(SERVER_OBJ)
	$(CC) -o server $(SERVER_OBJ)

read_process: $(READ_OBJ)
	$(CC) -o read_process $(READ_OBJ)

write_process: $(WRITE_OBJ)
	$(CC) -o write_process $(WRITE_OBJ)

clean:
	rm -f client server read_process write_process $(CLIENT_OBJ) $(SERVER_OBJ) $(READ_OBJ) $(WRITE_OBJ)
