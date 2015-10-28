all: main.c
	gcc -std=gnu11 -Wall -o dynamic_workout main.c LinkedList.c Queue.c menu.c
