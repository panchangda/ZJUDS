#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */
BinTree Insert(BinTree BST, ElementType X)
{
    BinTree new_node = malloc(sizeof(struct TNode));
    new_node->Data = X;
    new_node->Left = new_node->Right = NULL;
    if (!BST)
    {
        return new_node;
    }

    BinTree root = BST;
    BinTree tmp = BST;

    while (tmp)
    {
        if (X > tmp->Data)
        {
            if (!tmp->Right)
            {
                tmp->Right = new_node;
                break;
            }
            tmp = tmp->Right;
        }
        else if (X < tmp->Data)
        {
            if (!tmp->Left)
            {
                tmp->Left = new_node;
                break;
            }
            tmp = tmp->Left;
        }
        //already exists
        else
        {
            return root;
        }
    }
    return root;
}
//example tree:
/*
        5
    2       8
  1   4  6     10
0          7  9
*/
BinTree Delete(BinTree BST, ElementType X)
{
    BinTree root = BST;
    if (!Find(BST, X))
    {
        printf("Not Found\n");
    }
    else
    {   
        //delete root node
        if(root->Data==X){
            if(root->Left&&!root->Right){
                root = root->Left;
            }
            else if(root->Right&&!root->Left){
                root = root->Right;
            }
            else if(root->Left&&root->Right){
                BST=BST->Right;
                BinTree target = FindMin(BST);
                int newData = target->Data;
                //recursive 
                Delete(root,target->Data);
                root->Data = newData;
            }
            else{
                root = NULL;
            }
            //no need to free: delete root node will recursively delete a non-root node and free it
            return root;
        }
        //delete non-root node
        while ( 
        ((BST->Left&&(BST->Left)->Data != X) || !BST->Left)
        && ((BST->Right&&(BST->Right)->Data != X)||!BST->Right) 
        )
        {
            if (X > BST->Data)
            {
                BST = BST->Right;
            }
            else
            {
                BST = BST->Left;
            }
        }
        BinTree father = BST;
        if (father->Left&& (father->Left)->Data == X)
        {   
            BST=BST->Left;
            if(BST->Left&&BST->Right){
                BST = BST->Right;
                BinTree target = FindMin(BST);
                int newData = target->Data;
                //recursive delete target node
                Delete(root,target->Data);
                (father->Left)->Data = newData;
            }
            else if(BST->Left&&!BST->Right){   
                father->Left = BST->Left;
            }
            else if(BST->Right&&!BST->Left){
                father->Left = BST->Right;
            }
            else{
                father->Left = NULL;
            }
        }
        else
        {
            BST=BST->Right;
            if(BST->Left&&BST->Right){
                BST=BST->Right;
                BinTree target = FindMin(BST);
                int newData = target->Data;
                //recursive delete targetnode
                Delete(root,target->Data);
                (father->Right)->Data = newData;
            }
            else if(BST->Left&&!BST->Right){   
                father->Right = BST->Left;
            }
            else if(BST->Right&&!BST->Left){
                father->Right = BST->Right;
            }
            else{
                father->Right = NULL;
            }
        }
        free(BST);
    }
    return root;
}
Position Find(BinTree BST, ElementType X)
{
    while (BST)
    {
        if (X > BST->Data)
        {
            BST = BST->Right;
        }
        else if (X < BST->Data)
        {
            BST = BST->Left;
        }
        else
            return BST;
    }

    return NULL;
}
Position FindMin(BinTree BST)
{   
    if(!BST)
        return NULL;
    while (BST->Left)
    {
        BST = BST->Left;
    }
    return BST;
}
Position FindMax(BinTree BST)
{   
    if(!BST)
        return NULL;
    while (BST->Right)
    {
        BST = BST->Right;
    }
    return BST;
}

//functions to test on your own
/* 
void PreorderTraversal(BinTree BT)
{
    if (BT)
    {
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
void InorderTraversal(BinTree BT){
    if(BT){
        InorderTraversal(BT->Left);
        printf(" %d",BT->Data);
        InorderTraversal(BT->Right);
    }
}
*/