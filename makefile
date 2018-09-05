FLAG= -g -std=gnu11 -w

all: main.c bst.h bst.c
	gcc $(FLAG) main.c -o main

run: all
	./main

checkmem: all
	valgrind ./main

clean:
	rm main