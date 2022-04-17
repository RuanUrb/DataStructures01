#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAX_EX 19


//dynamic stack from scratch
typedef struct StackNode* StackNodePtr;

typedef struct StackNode
{
    char ch;
    StackNodePtr next;
}StackNode;

typedef struct 
{
    StackNodePtr top;
    int size;
}Stack;

void initializeStack(Stack *s)
{
    s->size = 0;
    s->top = NULL;
}

bool isEmptyStack(Stack *s)
{
    return (s->top == NULL);
}

int sizeOfEmptyStack(Stack *s)
{
    return (s->size);
}

void pileUpStack(Stack *s, char x)
{
    StackNodePtr new = malloc(sizeof(StackNode));
    new->ch = x;
    new->next = s->top;
    s->top = new;
    s->size++;
}

char unpileStack(Stack *s)
{
    char res = '0';
    if(isEmptyStack(s))
    {
        printf("Stack is already empty.\n");
        return res;
    }
    res = s->top->ch;
    StackNodePtr aux = s->top;
    s->top = s->top->next;
    free(aux);
    s->size--;
    return(res);
}

void printStack(Stack *s)
{
    printf("Stack = [");
    StackNodePtr var = s->top;
    while(var != NULL)
    {
        printf("%c ", var->ch);
        var = var->next;
    }
    printf("]\n");
}
//function that checks whether given number is (+, -, *, /)
bool isOperator(int c)
{
    return(c == 42 || c == 43 || c == 45 || c == 47 );
}

bool validNumber(char key )
{
    if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') return true;
    else return false;
}

//function that prints ldr and operations with values, based on literals or temp variables
void loadAndOp(char l1, char l2, char *op, FILE *file)
{
    if(validNumber(l1) && !(validNumber(l2))) fprintf(file, "LDR TEMP%c\nLDR %c\n%s TEMP%c %c\n", l1, l2, op, l1, l2);
    else if(validNumber(l1) && (validNumber(l2))) fprintf(file, "LDR TEMP%c\nLDR TEMP%c\n%s TEMP%c TEMP%c\n", l1, l2, op, l1, l2);
    else if(!(validNumber(l1)) && (validNumber(l2))) fprintf(file, "LDR %c\nLDR TEMP%c\n%s %c TEMP%c\n", l1, l2, op, l1, l2);
    else fprintf(file, "LDR %c\nLDR %c\n%s %c %c\n", l1, l2, op, l1, l2);
}

//converts ascii to string keywords
void convertOperator(int value, char **op)
{
    if(value == 42) *op = "MUL";
    else if(value == 43) *op = "ADD";
    else if(value == 45) *op = "SUB";
    else *op = "DIV";
}

//print str of a temp based on an arbitrary counting number 
void storeTemp(int count, FILE *file)
{
    fprintf(file, "STR TEMP%d\n", count);
}


int main(int argc, const char* argv[])

{
    char *op;
    int count_op = 0;
    char temp;
    Stack elements;
    initializeStack(&elements);
    FILE *inPtr = fopen(argv[1], "r");
    if(inPtr == NULL)
    {
        printf("Error upon opening input file. Exiting program.\n");
        return(-1);
    }
    FILE *ouPtr = fopen(argv[2], "w");
    if(ouPtr == NULL)
    {
        printf("Error upon opening output file. Exiting program.\n");
        return(-1);
    }
    char text[MAX_EX];
    fgets(text, MAX_EX, inPtr);         //stores content of file into text string
    for(size_t i = 0; i < strlen(text); i++)
    {
        if(!(isOperator(text[i])))
        {
            pileUpStack(&elements, text[i]);
        }
        else
        {   
            convertOperator(text[i], &op);
            count_op++;
            temp = count_op + '0';
            char old, older;
            old = unpileStack(&elements);
            older = unpileStack(&elements);
            loadAndOp(old, older, op, ouPtr);
            if(!(text[i+1] == '\0')) //when the operator is the last character, won't store temporaries
            {
                pileUpStack(&elements, temp);
                storeTemp(count_op, ouPtr);
            } 
        }
    }

    return 0;
}


