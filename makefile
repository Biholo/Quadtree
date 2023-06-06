EXEC = main
CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g -lMLV -lm

SRC_DIR = src/
INCLUDE_DIR = include/
BIN_DIR = bin/

OBJECTS = $(addprefix $(BIN_DIR), $(EXEC).o Point.o Global.o Graphique.o Outil.o Quadtree.o Option.o)

$(EXEC) : $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(BIN_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)


clean: 
	rm -f $(BIN_DIR)*.o $(EXEC)
	rm -r $(BIN_DIR)