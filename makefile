CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic
EXEC = rshell
SRC = src
BIN = ./bin
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS)
	mkdir -p $(BIN)
	$(CC) $(OBJECTS) -o $(BIN)/$(EXEC)


rshell: $(OBJECTS)
	mkdir -p $(BIN)
	$(CC) $(OBJECTS) -o $(BIN)/$(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
	rm -rf $(BIN)
