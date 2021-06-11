#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* !!!头节点不放数据!!! */
/* 你的代码将被嵌在这里 */
List Merge( List L1, List L2 ){
    List Head,l1,l2;
    List L = malloc(sizeof(struct Node));
    L->Next = NULL;
    Head = L;
    l1 = L1->Next;
    l2 = L2->Next;

    while(l1!=NULL&&l2!=NULL){
        if(l1->Data<=l2->Data){
            L->Next =l1;
            L = L->Next;
            l1 = l1->Next;
        }
        else{
            L->Next = l2;
            L = L->Next;
            l2 = l2->Next;
        }    
    }

    //connect remain nodes
    if(l1)  L->Next = l1;
    else    L->Next = l2;

    //output process
    L1->Next = L2->Next = NULL;
    return Head;
}