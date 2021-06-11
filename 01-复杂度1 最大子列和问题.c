#include <stdio.h>
int A[100000];

int main()
{
    //initialize parameters
    int K,max, tmp;
    max = tmp = 0;
    memset(A,0,sizeof(A));

    //input process
    scanf("%d",&K);
    for(int i=0;i<K;i++){
        scanf("%d",&A[i]);
    }

    //online processing
    for(int i=0;i<K;i++){
        tmp+=A[i];
        if(tmp>max)
            max = tmp;
        if(tmp<0)
            tmp = 0;
    }
    
    //output
    printf("%d",max);
    return 0;
}