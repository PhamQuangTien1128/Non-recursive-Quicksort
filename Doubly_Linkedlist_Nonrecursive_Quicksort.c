#include <stdio.h>
#include <stdlib.h>
#include "StackC.h"
#include "StackC.c"

#define in "in.txt"
#define out "out.txt"

typedef struct tagNode{
    int x;
    struct tagNode *pNext, *pPrev;
}Node;

typedef struct{
    Node* pHead;
    Node* pTail;
}LIST;

typedef struct {
    Node* left;
    Node* right;
    int count_left;
    int count_right;
}Pair;// luu dia chi cua node

Node* getNode(int k){
    Node* p = (Node*)malloc(sizeof(Node));
    if(p == NULL) return NULL;
    
    p->x = k;
    p->pNext = p->pPrev = NULL;
    return p;
}

void addTail(LIST*l, Node* p){
    if(l->pHead == NULL)
        l->pHead = l->pTail = p;
    else{
        l->pTail->pNext = p;
        p->pPrev = l->pTail;
        l->pTail = p;
    }
}

Node* InsertTail(LIST* l, int k){
    Node* p = getNode(k);
    if(p == NULL) return NULL;
    
    addTail(l,p);
    return p;
}

void printList(LIST l){
    for(Node* p = l.pHead; p; p = p->pNext)
        printf("%d\t",p->x);
}

int length(LIST l){
    int count = 0;
    for(Node* p = l.pHead; p; p = p->pNext)
        count++;
    return (count);
}

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

Node* searchAt(LIST l, int pos){
	Node* p = l.pHead;
	for(int i = 1; i < pos; i++, p = p->pNext);
	return p;
}


void QuickSort(LIST *l, Node* L, Node* R, STACK* stack){
    Pair *p = (Pair*)malloc(sizeof(Pair));
	p->left = L; p->right = R; p->count_left = 1; p->count_right = length(*l);
    pushStack(stack, p);
    int pivot;
    int count_L, count_R, count_i, count_j;
    Node *i, *j;
    while(!isEmpty(stack)){
        p = popStack(stack);
        //popStack(stack);
        L = p->left; R = p->right; i = L; j = R;
		count_L = p->count_left; count_R = p->count_right; count_i = count_L; count_j = count_R;
		Node* temp;
		int mid_pos = (count_L + count_R) / 2;
		temp = searchAt(*l, mid_pos);
		pivot = temp->x;
		do{
			while(i->x < pivot){
                i = i->pNext; count_i++;
            } 
			while(j->x > pivot){
                j = j->pPrev; count_j--;
            }
			if(count_i <= count_j){
				swap(&(i->x), &(j->x));
				i = i->pNext; count_i++;
				j = j->pPrev; count_j--;
			}
		}while(count_i <= count_j);
		
		if(count_L < count_j){
			p->left = L; p->right = j; p->count_left = count_L; p->count_right = count_j;
			pushStack(stack, p); 
		}
		p = (Pair*)malloc(sizeof(Pair)); // Cap dia chi moi 
		if(count_i < count_R){
			p->left = i; p->right = R; p->count_left = count_i; p->count_right = count_R;
			pushStack(stack, p); 
		}
    }
}

void read_file(LIST *l){
	FILE *fo;
	fo = fopen(in, "r");
	if(fo == NULL) exit(1);
	else{
		int n,x;
		fscanf(fo, "%d", &n);
		for(int i = 0; i < n; i++){
			fscanf(fo, "%d", &x);
			InsertTail(l, x);
		}
	}
	fclose(fo);
}

void write_file(LIST l){
	FILE *fo; 
	fo = fopen(out, "w");
	if(fo == NULL) exit(0);
	else{
		for(Node *p = l.pHead; p; p = p->pNext)
			fprintf(fo, "%d\t", p->x);
	}
	fclose(fo);
}

int main(void){
    LIST l;
//    int n, x;
    l.pHead = l.pTail = NULL;
/*    printf("Nhap so luong phan tu:");
    scanf("%d",&n);
    while(n <= 0){
        printf("Nhap so luong phan tu lon hon 0: ");
        scanf("%d",&n);
    }

    for(int i = 0; i < n; i++){
        scanf("%d",&x);
        InsertTail(&l,x);
    }*/
//    Pair *p = (Pair*)malloc(sizeof(Pair));
    STACK *stack = (STACK*)initStack();
    read_file(&l);
//    printList(l);
	QuickSort(&l, l.pHead, l.pTail, stack);
//	printList(l);
	write_file(l);
    closeStack(stack);
    free(stack); //free(p);
    return 0;
}

