OBJS = bit_permutation.o main.o
EXEC = main

$(EXEC): $(OBJS)
	gcc -o $(EXEC) $(OBJS)
	
$(EXEC).o: main.c
	gcc -c main.c

bit_permutation.o: bit_permutation.c
	gcc -c bit_permutation.c
