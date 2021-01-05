CC=gcc
SRC=../src/
INCLUDES=-lm
OPT=-O3
OBJ=graph.o queue.o

test-%.out : $(SRC)test-%.c $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $^ -o $@

test-ind.out : $(SRC)test-ind.c $(SRC)indicator.h
	$(CC) $(FLAGS) $(INCLUDES) $< -o $@

main.out : $(SRC)main.c $(OBJ)
	$(CC) $^ -o $@ $(FLAGS) $(OPT) $(INCLUDES)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDES)

clean :
	rm -rf *.o *.out 


