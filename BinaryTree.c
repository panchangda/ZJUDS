#include"stack.h"
#include<stdio.h>

#define ElementType int
#define MaxSize 10

typedef struct TreeNode *BiTree;
typedef BiTree position;
typedef struct TreeNode{
    ElementType Data;
    BiTree Left;
    BiTree Right;    
};

void PreOrderTraversal(BiTree BT)
{
    if(BT){
        printf("%d",BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}


void InOrderTraversal(BiTree BT)
{
    if(BT){
        InOrderTraversal(BT);
        printf("%d",BT->Data);
        InOrderTraversal(BT);
    }
}


void PostOrderTraversal(BiTree BT){
    if(BT){
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        printf("%d",BT->Data);
    }
}


//Non-Recursive
void Non_Recursive_PreOrderTraversal(BiTree BT)
{
    Stack S = CreateStack(MaxSize);
    while(BT||!IsEmpty(S)){
        while(BT){
            Push(S,BT);
            BT= BT->Left;
            printf("%d",BT->Data);
        }
        if(!IsEmpty(S)){
            BT = Pop(S);
            BT = BT->Right;
        }
    }
    
}
void Non_Recursive_InOrderTraversal(BiTree BT)
{
    Stack S = CreateStack(MaxSize);
    while(BT||!IsEmpty(S)){
        while(BT){
            push(S,BT);
            BT = BT->Left;
        }
        if(!IsEmpty(S)){
            BT = Pop(S);
            printf("%d",BT->Data);
            BT = BT->Right;
        }
    }
}
void Non_Recursive_PostOrderTraversal(BiTree BT)
{
    Stack S = CreateStack(MaxSize);
    while(BT||!IsEmpty(S)){
        while(BT){
            push(S,BT);
            BT = BT->Left;
        }
        if(!IsEmpty(S)){
            BT = Pop(S);
            BT = BT->Right;
        }
    }
}