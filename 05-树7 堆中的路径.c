#include <stdio.h>

int H[1001];
int size=0;

void insert(int value){
    int i;
    i = ++size;
    for(;H[i/2]>value;i/=2)
        H[i] = H[i/2];
    H[i] = value;
}

void printpath(int idx){
    while(idx!=1){
        printf("%d ",H[idx]);
        idx/=2;
    }
    printf("%d\n",H[1]);
}

int main()
{   
    H[0]=-10001;
    int N,M,value,idx;
    scanf("%d %d",&N,&M);
    for(int i=0;i<N;i++){
        scanf("%d",&value);
        insert(value);
    } 
    for(int i=0;i<M;i++){
        scanf("%d",&idx);
        printpath(idx);
    }
    // for(int i=0;i<N+1;i++){
    //     printf("%d ",H[i]);
    // }
    return 0;
}