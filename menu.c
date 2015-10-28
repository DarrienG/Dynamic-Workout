/*
 Authors:
    Maryann O'Connell
    Darrien Glasser
    Rosemary Greeley
 Computing II
 Final Project
 Description: menu.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "Header.h"

//display main menu
void display_menu(void);
void edit_menu(LinkedListPtr list);
void start_workout(QueuePtr queue);
void ready_set_go();
void clear_line(void);
void clear_file();

// Initializes queue, and allows the user to plan their workout
QueuePtr custom_workout(LinkedListPtr list);
QueuePtr premade_workout();

//passed list of exercises and custom file in case user chooses to save workout.
void edit_file(LinkedListPtr list);

//used to initalize multiple fields when user adds an exercise
Data getData(LinkedListPtr list);

void clear_buffer(void);

char* line = "\n\n========================================================\n\n";
extern bool custom;

void menu(LinkedListPtr list)
{
    int choice;
    QueuePtr queue = NULL;
    
    //first display to user
    display_menu();
    fscanf(stdin, "%d", &choice);
    clear_buffer();
    
    while(choice != 6)
    {
        printf("%s", line);
        switch (choice) {
            case 1:
                printf("%s", line);
                display(list);
                break;
            case 2:
                printf("%s", line);
                edit_menu(list);
                break;
            case 3:
                choice = -9;

                while(choice != 1 && choice != 2){
                    printf("[1] Create a custom workout\n");
                    printf("[2] Choose a premade workout\n");
                    fscanf(stdin, "%d", &choice);
                }

                if (choice == 1)
                {
                    queue = custom_workout(list);
                }
                else{
                    queue = premade_workout();
                }
                printf("%s", line);
                
                break;
            case 4:
                start_workout(queue);
                break;
            case 5:
                edit_file(list);
                break;
            case 7:
                if (custom == true)
                {
                    clear_file();
                }
                break;
            default:
                break;
        }
        display_menu();
        fscanf(stdin, "%d", &choice);
        clear_buffer();
        printf("%s", line);
    }
    if(queue != NULL)
    {
        destroyQueue(queue);
    }
}

//template for menu options; modify as necessary
void display_menu()
{
    printf("Please select from the following options:\n\n");
    printf("[1] Display all exercises\n");
    printf("[2] Edit list of exercises\n");
    printf("[3] Plan workout\n");
    printf("[4] Begin workout\n");
    printf("[5] Save\n");
    printf("[6] Exit Menu\n");

    if (custom)
    {
        printf("\nCustom file editing menu:\n");
        printf("[7] Clear the custom file\n");
    }
}

void edit_menu(LinkedListPtr list){
    int choice, input;
    Data exercise;
    char* line = malloc(128);
    char s[128];
    display(list); 
    choice = -9;
    
    while(choice != 3){
        printf("What would you like to do with your exercises?\n");
        printf("[1] Add an exercise\n");
        printf("[2] Delete an exercise\n");
        printf("[3] Return to the main menu\n");
        
        fscanf(stdin, "%d", &choice);
        clear_buffer();
        switch(choice){
                
            case 1:
                printf("What exercise would you like to add to the list?\n");
                fgets(line, 256, stdin);
                strcpy(s, line);
                exercise.name = strdup(newLineDestroyer(s));
                add(list, exercise);
                clear_buffer();
                break;
                
            case 2:
                printf("Choose an exercise to remove [number]\n");
                fscanf(stdin, "%d", &input);
                remove_at(list, input - 1);
                break;
                
            case 3:
                break;
                
            default:
                printf("Please choose a valid option.\n");
                break;
        }
        
    }
    
}

//get data for exercise when user wishes to add to queue
//intended to be called within workout_submenu
Data getData(LinkedListPtr list)
{
    Data exercise;
    int choice;
    display(list);


    printf("Choose an exercise to add [number]\n");
    fscanf(stdin, "%d", &choice);
    clear_buffer();
    exercise = check_data(list, choice - 1);
    printf("Would you like to time this exercise or count reps?\n");
    printf("Select [0] to enter the number of reps, or [1] to enter time to complete the exercise.\n");
    fscanf(stdin, "%d", &exercise.timeOrReps);
    switch(exercise.timeOrReps)
    {
        case 0:
            printf("Enter the number of reps: ");
            fscanf(stdin, "%d", &exercise.reps);
            break;
        case 1:
            printf("Enter the time to complete the exercise, in seconds: ");
            fscanf(stdin, "%d", &exercise.reps);
            //exercise.reps initalized to 0 if they failed to provide the time or number of reps. (Shortcut for now)
            //alternatively, we could check for error and prompt user again.
            break;
        default:
            exercise.reps = 0;
            break;
    }
    clear_buffer();
    return exercise;
}

QueuePtr custom_workout(LinkedListPtr list){
    int choice;
    Data data;
    QueuePtr queue;
    choice = -9;
    
    queue = initQueue();
    
    while(choice != 0){
        data = getData(list);
        printf("Do you want to continue?\n");
        printf("[1] to continue, [0] to quit\n");
        fscanf(stdin, "%d", &choice);
        enqueue(queue, data);
    }
    return queue;
}

QueuePtr premade_workout(){
    Data data;
    int choice = -9;
    char* fileName;
    char* line = malloc(MAXSIZE);
    char* token;
    char s[MAXSIZE];
    QueuePtr queue;
    
    queue = initQueue();
    
    while(choice != 1 && choice != 2 && choice != 3){
        printf("What premade workout would you like to choose?\n");
        printf("[1] Aerobic\n");
        printf("[2] Strength training\n");
        printf("[3] Core Exercises\n");
        fscanf(stdin, "%d", &choice);
    }
    
    if (choice == 1)
    {
        fileName = "premade/aerobic.txt";
    }
    else if (choice == 2)
    {
        fileName = "premade/strength.txt";
    }
    else{
        fileName = "premade/core.txt";
    }
    
    FILE *active_file = fopen(fileName, "r");
    if(active_file == NULL)
    {
        fprintf(stderr, "%s failed to open.\n", fileName);
    }

    do{
        fgets(line, MAXSIZE, active_file);
        newLineDestroyer(strdup(line));
        
        strcpy(s, line);
        token = strtok(s, ",");
        if(token) {
            data.name = newLineDestroyer(strdup(token));
            token = strtok(NULL, ",");
        }
        if(token){
            data.fileName = newLineDestroyer(strdup(token));
            token = strtok(NULL, ",");
        }
        if(token){
            data.timeOrReps = atoi(newLineDestroyer(strdup(token)));
            token = strtok(NULL, ",");
        }
        if(token){
            data.reps = atoi(newLineDestroyer(strdup(token)));
            token = strtok(NULL, ",");
        }
        enqueue(queue, data);
    }
    while(!feof(active_file));
    
    return queue;
}

void start_workout(QueuePtr queue){
    Data data;
    int i;
    if (queue == NULL)
    {
        printf("Your workout is empty, add something to it to start!\n");
        return;
    }
    ready_set_go();

    while(!isEmptyQ(queue)){
        data = dequeue(queue);
        // Will not output anything if data.fileName is NULL
        // Will only happen if workout is custom
        animate(data.fileName);
        
        i = data.reps;
        printf("******%s******\n\n", data.name);
        
        // We want time
        if (data.timeOrReps == 1)
        {
            printf("Press <ENTER> to start\n");
            fgetc(stdin);
            for (; i > 0; --i)
            {
                printf("%d\n", i);
                sleep(1);
            }
        }
        
        // We want reps
        // if (data.timeOrReps == 0)
        else
        {
            printf("%d reps\n", i);
            printf("Hit <ENTER> when you've finished\n");
            fgetc(stdin);
        }
    }
    animate("assets/complete.txt");
    printf("\n\n");
}

void clear_buffer(void)
{
    char c;
    scanf("%c", &c);
    while(c!= '\n')
    {
        scanf("%c", &c);
    }
}

void edit_file(LinkedListPtr list){
    FILE *fp = fopen("CustomUserFile.txt", "w");
    char file[] = "CustomUserFile.txt";
    if(fp == NULL)
    {
        fprintf(stderr, "%s failed to open.\n", file);
    }

    NodePtr runningNode = list -> head;
    while(runningNode != NULL){
        fprintf(fp, "%s", runningNode -> data.name);
        if (runningNode -> next != NULL)
        {
            fprintf(fp, "\n");
        }
        runningNode = runningNode -> next;
    }
    fclose(fp);
    printf("Successfully saved workouts!\n");
}

void ready_set_go(){
    clear_line();
    animate("assets/ready.txt");
    sleep(1);
    clear_line();
    animate("assets/set.txt");
    sleep(1);
    clear_line();
    animate("assets/go.txt");
    printf("\n\n\n");
    sleep(1);
}

void clear_line(){
    int i;
    for (i = 0; i < 100; ++i)
    {
        printf("\n");
    }
}

void clear_file(){
    fclose(fopen("CustomUserFile.txt", "w"));
    printf("Custom file cleared! \nPlease restart the program to go back to the default file.\n\n");
}