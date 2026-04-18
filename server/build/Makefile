CC = gcc
CFLAGS = -Wall -pthread
QUITE = @
MKDIR = mkdir -p
RM = rm -rf
SRC = ../src/server.c
BIN_DIR = ../bin

TARGET = $(BIN_DIR)/server

all:
	$(QUITE)$(MKDIR) $(BIN_DIR)
	$(QUITE)$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	$(QUITE)$(RM) $(BIN_DIR)
