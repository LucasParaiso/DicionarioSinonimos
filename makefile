OBJS=main.o avl.o
main: $(OBJS)
	gcc -o main $(OBJS)
	
avl.o: avl.c avl.h
	gcc -c avl.c
	
main.o: main.c avl.h
	gcc -c main.c
