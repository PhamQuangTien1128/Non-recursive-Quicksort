#ifndef STACKC_H
#define STACKC_H

void* initStack();
void closeStack(void* stack);
void* topStack(void* stack);
int isEmpty(void* stack);
void pushStack(void* stack, void* item);
void* popStack(void* stack);


#endif

