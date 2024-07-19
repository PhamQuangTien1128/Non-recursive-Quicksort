#include <stdio.h>
#include <stdlib.h>
#include "StackC.h"

typedef struct tagnode{
	void* data;
	struct tagnode* next;
}NODE;

typedef struct{
	NODE* head;
}STACK;

void* initStack(){
	STACK* l = NULL;
	void* buf = malloc(sizeof(STACK));
	l = (STACK*)buf;
	if(l == NULL) return NULL;
	l->head = NULL;
	return l;
}

void closeStack(void* stack){
	STACK* l = (STACK*)stack;
	NODE* nod = NULL;
	if(l == NULL) return;
	nod = l->head;
	while(nod != NULL){
		NODE* temp = nod->next;
		free(nod);
		nod = temp;
	}
}

void *topStack(void* stack){
	STACK* l = (STACK*)stack;
	if(l == NULL||l->head == NULL)
		return NULL;
	
	return l->head->data;
}

int isEmpty(void* stack){
	return(topStack(stack) == NULL);
}

static NODE* makeNode(void* dat){
	NODE* nod = (NODE*)malloc(sizeof(NODE));
	if(nod != NULL){
		nod->data = dat;
		nod->next = NULL;
	}
	return nod;
}

void pushStack(void* stack, void* k){
	STACK* l = (STACK*)stack;
	if(l != NULL){
		NODE* temp = l->head;
		NODE* nod = makeNode(k);
		if(nod != NULL){
			l->head = nod;
			nod->next = temp;
		}
	}
}

void* popStack(void* stack){
	STACK* l = (STACK*)stack;
	if(l != NULL && l->head != NULL){
		NODE* nod = l->head;
		void* dat = nod->data;
		l->head = l->head->next;
		free(nod);
		return dat;
	}
	return NULL;
}
