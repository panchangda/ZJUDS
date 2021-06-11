/**
     3

    /  \

    2    7

    /       /  \ 

  0        4   6

 /              /

1             5
**/
#include <stdio.h>
#include<queue>
using namespace std;

typedef struct TreeNode
{
  char left,right;
}node;

node nodes[11];
int count = 0;

void recursion(int root){
  if(nodes[root].left!='-'){
    recursion(nodes[root].left - '0');
    count++;
  }
  if(nodes[root].right!='-'){
    recursion(nodes[root].right - '0');
    count++;
  }
}

bool IsRoot(int root,int n){
  count = 0;
  recursion(root);
  return count==n-1?true:false;
}

void bfs(int root){
  queue <int> q;
  q.push(root);
  int first=1;
  while(!q.empty()){
    int t = q.front();
    q.pop();
    if(nodes[t].left=='-'&&nodes[t].right=='-'){
      if(first){
        printf("%d",t);
        first--;
      }
      else 
        printf(" %d",t);
    }
            
    if(nodes[t].left!='-')
      q.push(nodes[t].left-'0');
    if (nodes[t].right!='-')
      q.push(nodes[t].right-'0');  
  }
}

int main()
{
  int n,root;
  scanf("%d\n", &n);
  for (int i=0;i< n; i++)
  { 
    scanf("%c %c\n", &nodes[i].left, &nodes[i].right);
  }

  for(int i=0;i<n;i++){
    if(n==1){
      root = i;
      break;
    }
    else if(nodes[i].left!='-'&&nodes[i].right!='-'
    &&IsRoot(i,n)){
      root = i;
      break;
    } 
  }

  bfs(root);
  return 0;
}