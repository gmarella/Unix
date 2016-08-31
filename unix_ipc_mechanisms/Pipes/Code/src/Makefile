CODE_BASE_DIR=../
HDR_INC_PATH=$(CODE_BASE_DIR)include

CC = gcc
CFLAGS += -g -Wall -Werror
CFLAGS += -I$(HDR_INC_PATH)

SRC_OBJS=pipe_ipc.o
TEST_MAIN_TARGET=test_pipe

$(TEST_MAIN_TARGET): $(SRC_OBJS)
	$(CC) $(CFLAGS) $(SRC_OBJS) -o $@

.PHONY: all
all: $(TEST_MAIN_TARGET)

clean:
	rm -rf .*o
	rm -rf .*i
	rm -rf *.s
	rm -rf $(TEST_MAIN_TARGET)
