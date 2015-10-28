/*
 Authors:
    Maryann O'Connell
    Darrien Glasser
    Rosemary Greeley
 Computing II
 Final Project
 Description: Header.h
 */

#ifndef MASTER_HEADER
#define MASTER_HEADER 

#define MAXSIZE 128


// For timeOrReps:
// 1 = time, 0 = reps
typedef struct{
    char *name;
    char *fileName;
    int timeOrReps;
    int reps;
}Data, *DataPtr;

typedef struct node{
    Data data;
    struct node *next;
}Node, *NodePtr;

typedef struct{
    NodePtr head;
    NodePtr tail;
    int size;
}LinkedList, *LinkedListPtr;

typedef struct{
    NodePtr head;
    NodePtr tail;
    int size;
}Queue, *QueuePtr;

// Linked list section

LinkedListPtr initLinkedList(void);

Data check_data(LinkedListPtr list, int position);

void display(LinkedListPtr list);

void add(LinkedListPtr list, Data data);

void remove_at(LinkedListPtr list, int position);

void emptyList(LinkedListPtr list);

int isEmptyList(LinkedListPtr list);

LinkedListPtr destroy(LinkedListPtr list);


// Queue section
QueuePtr initQueue(void);

void destroyQueue(QueuePtr Q);

void enqueue(QueuePtr Q, Data data);

Data dequeue(QueuePtr Q);

int isEmptyQ(QueuePtr Q);

void emptyQ(QueuePtr Q);

int getSize(QueuePtr Q);


// User section

void menu(LinkedListPtr LinkedListPtr);

char* newLineDestroyer(char* line);

void animate(char* name);

// Displays the list of workouts and runs until the user quits
// Inputs into queue via userInput()
void mainMenu(LinkedListPtr list);

// Takes user input, makes choice based on number in linked list
// Adds choice to queue of workouts
int userInput(LinkedListPtr list, int choice);

#endif
