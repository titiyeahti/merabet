CC=gcc
SRC=../src/
INCLUDES=-lm
OPT=-O3
OBJ=file-handler.o graph.o queue.o problem.o algo.o

ifeq ($(RAND), 1)
FLAGS= -ansi -Wall -Wextra -g $(OPT) -DRAND 
else 
FLAGS=-ansi -Wall -Wextra -g $(OPT)
endif

all : main.out single.out

run : main.out
	./main.out captANOR150_7_4.dat

run_single : single.out
	./single.out ../instances/captANOR150_7_4.dat 3 2 3 16 150

single.out : $(SRC)single.c $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $^ -o $@

main.out : $(SRC)main.c $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $^ -o $@

test : test-graph.out test-problem.out test-file-handler.out test-greedy.out

test-%.out : $(SRC)test-%.c $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $^ -o $@

test-ind.out : $(SRC)test-ind.c $(SRC)indicator.h
	$(CC) $(FLAGS) $(INCLUDES) $< -o $@

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDES)

clean :
	rm -rf *.o *.out 


