#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<string.h>

using namespace std;

typedef struct node{
    int data;
    struct node *left,*right;
}* treenode;

stack<treenode> s;
int result[31],num=0;

void postOrder(treenode root){
    if(root){
        postOrder(root->left);
        postOrder(root->right);
        result[num++]=root->data;
    }
}

int main()
{
    int n;
    treenode fatherNode,tmpNode,root;
    int isRoot=1,poped=0;
    scanf("%d",&n);
    for(int i=0;i<2*n;i++){
        char op[5];
        int data;
        scanf("%s",&op);
        if(strcmp(op,"Push")==0){
            scanf("%d",&data);
            treenode newNode = (treenode)malloc(sizeof(struct node));
            newNode->data = data;
            newNode->left = NULL;
            newNode->right = NULL;
            if(isRoot){
                s.push(newNode);
                isRoot--;
                root = newNode;
            }
            else{
                if(!poped){
                    tmpNode = s.top();
                }
                else{
                    tmpNode = fatherNode;
                }
                if(tmpNode->left == NULL){
                        tmpNode->left = newNode;
                    }
                else tmpNode->right = newNode;
                s.push(newNode);
                poped = 0;
            }
            // printf("PUSH %d",newNode->data);
        }
        else{
            fatherNode = s.top();
            s.pop();
            poped = 1;
            // printf("POP %d",fatherNode->data);
        }
    }

    postOrder(root);

    for(int i=0;i<n-1;i++)
        printf("%d ",result[i]);
    printf("%d",result[n-1]);

    return 0;
}