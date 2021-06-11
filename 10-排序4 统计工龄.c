#include<stdio.h>
#include<stdlib.h>
int cmp(int *a, int *b){
    return *a-*b;
}

int main(){
    int N;
    scanf("%d",&N);
    int A[N];
    for(int i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    
    qsort(A,N,sizeof(int),cmp);

    int tmp = 0,count=0;
    for(int i=0;i<N;i++){
        if(A[i]==tmp)
            count++;
        else if(A[i]>tmp){
            if(count)
                printf("%d:%d\n",tmp,count);
            tmp=A[i];
            count=1;
        }
    }
    if(count)
        printf("%d:%d\n",tmp,count);
    return 0;
}