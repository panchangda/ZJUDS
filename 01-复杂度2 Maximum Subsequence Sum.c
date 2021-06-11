#include<stdio.h>
#include<stdlib.h>
int A[10000];
int main(){
    //initialize
    int N = 0;
    int ThisSum = 0;
    int MaxSum = -1;
    int x, y, z = 0;
    memset(A,0,10000);

    //input processing
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&A[i]);
    }

    //online processing algorithm
    for(int i=0;i<N;i++){
        ThisSum+=A[i];
        if(ThisSum>MaxSum){
            MaxSum=ThisSum;
            x=z;
            y=i;
        }            
        else if(ThisSum<0){
             ThisSum = 0;
             z = i + 1;
        }    
    }

    //output processing
    // all numbers are negative
    if(MaxSum<0){
        printf("0 ");
        printf("%d ",A[0]);
        printf("%d" , A[N-1]);
    }
    else{
        printf("%d ", MaxSum);
        printf("%d ",A[x]);
        printf("%d" , A[y]);
    }
       
    return 0;
}
