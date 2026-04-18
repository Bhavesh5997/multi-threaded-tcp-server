CC = gcc
CFLAGS = -Wall -pthread
QUITE = @
MKDIR = mkdir -p
RM = rm -rf
SRC = ../src/client.c
BIN_DIR = ../bin

TARGET = $(BIN_DIR)/client

all:
	$(QUITE)$(MKDIR) $(BIN_DIR)
	$(QUITE)$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	$(QUITE)$(RM) $(BIN_DIR)
