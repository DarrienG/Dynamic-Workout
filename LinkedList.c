/*
 Authors:
    Maryann O'Connell
    Darrien Glasser
    Rosemary Greeley
 Computing II
 Final Project
 Description: LinkedList.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

LinkedListPtr initLinkedList(void){
    
    LinkedListPtr list;
    
    if((list = (LinkedListPtr)malloc(sizeof(LinkedListPtr))) == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    return list;
}

Data check_data(LinkedListPtr list, int position){
    
    NodePtr ptr = list->head;
    int i = 0;
    if(position < 0){
        printf("Index error.\n");
        exit(1);
    }
    while(ptr != NULL && (i < position)){
        ptr = ptr->next;
        i++;
    }
    if(ptr != NULL) {
        return ptr->data;
    } else {
        printf("Index out of bounds\n");
        exit(1);
    }
}

void display(LinkedListPtr list){
    
    int i;
    NodePtr node = list->head;
    
    printf("\nYour workouts: \n");
    if(list->head == NULL)
        printf("Empty.\n");
    
    i = 0;
    while(node != NULL){
        printf("[%d] %s\n", i + 1, node->data.name);
        node = node->next;
        i++;
    }

    printf("\n\n");
    
    return;
}

void add(LinkedListPtr list, Data data)
{
    NodePtr newNode = malloc(sizeof(Node));
    NodePtr runningNode = list -> head;
    newNode -> data = data;
    newNode -> next = NULL;
    
    if (list -> head == NULL && list -> tail == NULL)
    {
        list -> head = newNode;
    }
    else{
        while(runningNode -> next != NULL){
            runningNode = runningNode -> next;
        }
        runningNode -> next = newNode;
        
    }
}

void remove_at(LinkedListPtr list, int position){
    
    int pos = 0;
    NodePtr dummy, ptr, temp;
    
    dummy = (NodePtr)malloc(sizeof(Node));
    dummy->next = list->head;
    ptr = dummy;
    while(ptr != NULL && pos < position){
        ptr = ptr->next;
        pos++;
    }
    if(ptr != NULL){
        temp = ptr->next;
        if(temp->next != NULL){
            ptr->next = temp->next;
            free(temp);
        }
    }
    list->head = dummy->next;
    free(dummy);
    
    return;
}

void emptyList(LinkedListPtr list){
    
    NodePtr ptr, ptrNext;
    
    ptr = list->head;
    ptrNext = list->head;
    list->head = NULL;
    
    while(ptr != NULL){
        ptrNext = ptr->next;
        free(ptr);
        ptr = ptrNext;
    }
    
    return;
}

int isEmptyList(LinkedListPtr list){
    if(list->head == NULL){
        return 1;
    } else {
        return 0;
    }
}

LinkedListPtr destroy(LinkedListPtr list){
    
    if(list!= NULL){
        emptyList(list);
        free(list);
    }
    
    return NULL;
}