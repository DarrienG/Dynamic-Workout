/*
 Authors:
    Maryann O'Connell
    Darrien Glasser
    Rosemary Greeley
 Computing II
 Final Project
 Description: Queue.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

QueuePtr initQueue(void)
{
    QueuePtr Q;
    if((Q = (QueuePtr)malloc(sizeof(Queue))) == NULL)
    {
        printf("Something went wrong while allocating memory.\n");
        exit(1);
    }
    
    Q->head = NULL;
    Q->tail = NULL;
    Q->size = 0;
    return Q;
}

void destroyQueue(QueuePtr Q)
{
    if(isEmptyQ(Q))
    {
        free(Q);
    }
    else
    {
        emptyQ(Q);
        if(isEmptyQ(Q))
        {
            free(Q);
        }
    }
}

void enqueue(QueuePtr Q, Data data)
{
    NodePtr newNode;
    
    newNode = (NodePtr)malloc(sizeof(Node));
    if(newNode == NULL)
    {
        printf("Something went wrong while mallocing space for a new node!");
        exit(1);
    }
    
    newNode->data = data;
    newNode->next = NULL;
    if(Q->head == NULL)
    {
        Q->tail = newNode;
        Q->head = newNode;
    }
    else if(Q->head == Q->tail)
    {
        Q->tail->next = newNode;
        Q->tail = newNode;
        Q->head->next = Q->tail;
    }
    else
    {
        Q->tail->next = newNode;
        Q->tail = newNode;
    }
    Q->size = Q->size + 1;
}

Data dequeue(QueuePtr Q)
{
    NodePtr temp_node;
    Data temp;
    if(Q->head == NULL)
    {
        printf("There is no node to remove!");
    }
    else
    {
        temp = Q->head->data;
        temp_node = Q->head;
        Q->head = Q->head->next;
        free(temp_node);
        Q->size = Q->size - 1;
    }
    return temp;
}

int isEmptyQ(QueuePtr Q)
{
    if(getSize(Q) == 0)
    {
        return 1;
    }
    return 0;
}

void emptyQ(QueuePtr Q)
{
    while(Q->head != NULL)
    {
        dequeue(Q);
    }
}

Data getFront(QueuePtr Q)
{
    return Q->head->data;
}

int getSize(QueuePtr Q)
{
    return Q->size;
}