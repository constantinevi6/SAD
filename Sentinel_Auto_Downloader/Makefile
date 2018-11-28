CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra -g

BIN		:= bin
SRC		:= src
INCLUDE	:= -Iinclude
INCLUDE_PC	:= pkg-config --cflags libcurl
LIB		:= -Llib64
LIB_PC	:= pkg-config --libs libcurl libssl libcrypto
LIBRARIES	:= -lxerces-c-3.2 -lstdc++fs
LDFLAGS := 

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= sad.exe
else
EXECUTABLE	:= sad
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) $(INCLUDE) $(shell $(INCLUDE_PC)) $(LIB) $(LDFLAGS) $(shell $(LIB_PC)) $^ -o $@ $(LIBRARIES)
