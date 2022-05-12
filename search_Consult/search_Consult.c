#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Circular List structuring
typedef struct ListNode *PtrListNode;

typedef struct ListNode
{
    int code;
    char *info;
    PtrListNode next, previous;
}ListNode;

typedef struct 
{
    int size;
    PtrListNode outset;
}List;

void initializeList(List *l)
{
    l->size = 0;
    PtrListNode dummy = malloc(sizeof(ListNode));
    dummy->code = -999999999;
    dummy->info = "";
    dummy->next = dummy;
    dummy->previous = dummy;
    l->outset = dummy;
}

bool listIsEmpty(List *l)
{
    return(l->size == 0);
}

int listSize(List *l)
{
    return(l->size);
}

void listAppend(List *l, int value, char *data)
{
    PtrListNode new = malloc(sizeof(ListNode));
    new->code = value;
    new->info = data;
    if(listIsEmpty(l))
    {
        new->previous = l->outset;
        new->next = l->outset;
        l->outset->next = new;
        l->outset->previous = new;
    }
    else if(value <= l->outset->next->code)
    {
        new->previous = l->outset;
        new->next = l->outset->next;
        l->outset->next->previous = new;
        l->outset->next = new;
    }
    else if(value >= l->outset->previous->code)
    {
        new->previous = l->outset->previous;
        new->next = l->outset;
        new->previous->next = new;
        l->outset->previous = new;
    }
    else if(value > l->outset->next->code && value < l->outset->previous->code)
    {
        PtrListNode aux = l->outset;
        while(aux->next->code <= value) aux = aux->next;
        new->next = aux->next;
        new->previous = aux;
        aux->next = new;
        new->next->previous = new;
    }
    l->size++;
}

void searchListAndPrint(List *l, int value, FILE *output)
{
    PtrListNode aux;
    for(aux = l->outset->next; aux != l->outset; aux = aux->next)
    {
        if(aux->code == value)
        {
            fprintf(output, "%s\n", aux->info);
            return;
        }
    }
    fprintf(output, "Data not found.\n");
}

void ascendingPrint(List *l, FILE *output)
{
    PtrListNode aux;
    for(aux = l->outset->next; aux != l->outset; aux = aux->next) fprintf(output, "%s\n", aux->info);
}

void descendingPrint(List *l, FILE *output)
{
    PtrListNode aux;
    for(aux = l->outset->previous; aux != l->outset; aux = aux->previous) fprintf(output, "%s\n", aux->info);
}

int main(int argc, const char *argv[])
{
    //exception treatment
    if(argc != 3)
    {
        printf("Number of arguments incorret.\nExiting program...\n");
        return(-1);
    }
    FILE *inputPtr = fopen(argv[1], "w");
    FILE *outputPtr = fopen(argv[2], "w");
    if(inputPtr == NULL)
    {
        printf("Exception upon opening input file.\nExiting program...\n");
        return(-1);
    }
    if(outputPtr == NULL)
    {
        printf("Exception upon opening output file.\nExiting program...\n");
    }
    List heroList;
    initializeList(&heroList);

    //adds file content to data string
    char *data;
    long length;
    fseek(inputPtr, 0, SEEK_END);
    length = ftell(inputPtr);
    fseek(inputPtr, 0, SEEK_SET);
    data = (char*)calloc(length, sizeof(char));
    fread(data, sizeof(char), length, inputPtr);

    //line by line parsing #1
    const char jump[2] = "\n";
    char *line;
    line = strtok(data, jump);
    int flag = 0;
    char strCode[4] = "";
    int code;

    //line by line parsing #2
    while(line != NULL)
    {
        if(line[0] == '{')
        {
            for(int i = 1; line[i] != ','; i++) strncat(strCode, &line[i], 1);
            code = atoi(strCode);
            listAppend(&heroList, code, line);
            strcpy(strCode, "");
        }
        else if(line[0] == '1' && flag == 0) ascendingPrint(&heroList, outputPtr);
        else if(line[0] == '2' && flag == 0) descendingPrint(&heroList, outputPtr);
        else if(line[0] == '3' && flag == 0) flag = 1;
        else
        {
            if(flag == 1)
            {
                int searchCode = atoi(line);
                searchListAndPrint(&heroList, searchCode, outputPtr);
                return 0;
            }
            else
            {
                fprintf(outputPtr, "Invalid file formatting.\n");
                return 0;
            }
        }
        line = strtok(NULL, jump);
    }

    return 0;
}
