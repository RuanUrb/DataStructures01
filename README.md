Simple program that reads file containing reverse Polish notation expressions and translate it 
into a intermediate set of (arbitrary) compiling instructions through a dynamically-allocated stack.

EX 1:

INPUT:
ABC+*

OUTPUT:
LDR C
LDR B
ADD C B
STR TEMP1
LDR TEMP1
LDR A
MUL TEMP1 A

EX 2:

INPUT:

ZX-GF+/

OUTPUT:
LDR X
LDR Z
SUB X Z
STR TEMP1
LDR F
LDR G
ADD F G
STR TEMP2
LDR TEMP2
LDR TEMP1
DIV TEMP2 TEMP1
