/*
 Authors:
    Maryann O'Connell
    Darrien Glasser
    Rosemary Greeley
 Computing II
 Final Project
 Description: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include <stdbool.h>

#define MAXSIZE 128

bool custom = false;

int main(int argc, const char * argv[])
{
    int i = 0;
    long int len = 0;
    LinkedListPtr list;
    Data data;
    FILE* fp1, *fp2, *active_file;
    char file1[] = "CustomUserFile.txt";
    char file2[] = "Default.txt";
    char* line = malloc(MAXSIZE);
    char s[MAXSIZE];
    char *token;
    
    if(line == NULL)
    {
        fprintf(stderr, "Error allocating memory.");
        exit(1);
    }
    
    // Attempts to open user created file. If user file doesn't exist,
    // or is empty, opens the default file
    fp1 = fopen(file1, "r");
    if(fp1 == NULL)
    {
        fprintf(stderr, "%s not found.\n", file1);
    }
    else
    {
        fseek(fp1, 0, SEEK_END);
        len = ftell(fp1);
    }
    
    if(fp1 == NULL || len == 0)
    {
        fclose(fp1);
        fp2 = fopen(file2, "r");
        if(fp2 == NULL)
        {
            fprintf(stderr, "%s failed to open.\n", file2);
        }
        active_file = fp2;
        custom = false;
    }
    else
    {
        active_file = fp1;
        rewind(active_file);
        custom = true;
    }
    
    list = initLinkedList();
    
    do
    {
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
        
        add(list, data);
        i++;
    }
    while(!feof(active_file));
    
    menu(list);

    free(line);
    free(data.name);
    // Makes small memory leak when default file is chosen
    // Throws error if custom file is chosen
    //free(data.fileName);    
    fclose(active_file);
    destroy(list);

    return 0;
}

char* newLineDestroyer(char* line){
    line[strcspn(line, "\n")] = 0;
    return line;
}

// Takes the name of a file, opens the file, and outputs
// every character to the console.
// Good for showing unicode/ASCII pictures.
void animate(char* name){
    FILE *fp = fopen(name, "r");
    
    if (fp == NULL)
    {
        return;
    }
    char temp;
    while((temp = fgetc(fp)) != EOF){
        printf("%c", temp);
    }
    fclose(fp);
}
