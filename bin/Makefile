CC=gcc
SRC=../src/
INCLUDES=-lm
OPT=-O3
OBJ=graph.o queue.o departager.o

graph-gen.out : $(SRC)graph-gen.c $(OBJ)
	$(CC) $^ -o $@ $(FLAGS) $(OPT) $(INCLUDES)

main.out : $(SRC)main.c $(OBJ)
	$(CC) $^ -o $@ $(FLAGS) $(OPT) $(INCLUDES)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDES)

clean :
	rm -rf *.o *.out 


