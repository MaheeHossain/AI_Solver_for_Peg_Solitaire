all: pegsol

pegsol: peg_solitaire.c ai.o hashtable.o stack.o utils.o
	gcc -g -o pegsol peg_solitaire.c ai.o hashtable.o stack.o utils.o -g -lm

ai.o : ai.c ai.h
	gcc -g -o ai.o -c -Wall ai.c

hashtable.o: hashtable.c hashtable.h
	gcc -g -o hashtable.o -c -Wall hashtable.c

stack.o: stack.c stack.h
	gcc -g -o stack.o -c -Wall stack.c

utils.o: utils.c utils.h layouts.h
	gcc -g -o utils.o -c -Wall utils.c

run: pegsol
	valgrind --leak-check=full --track-origins=yes ./pegsol 2