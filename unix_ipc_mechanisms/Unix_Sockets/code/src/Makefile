CODE_BASE_DIR=..
HDR_PATH=$(CODE_BASE_DIR)/include

CC = gcc
CFLAGS += -g -Wall -Werror
CFLAGS += -I$(HDR_PATH)

CLIENT_OBJS= client_socket.o 
SERVER_OBJS= server_socket.o
CLIENT_TARGET= client_app
SERVER_TARGET= server_app

$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $@

$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@

.phony:all

all: $(SERVER_TARGET) $(CLIENT_TARGET)

clean:
	rm -rf *.o
	rm -rf *.i
	rm -rf *.s
	rm -rf $(SERVER_TARGET) $(CLIENT_TARGET)

