#include<stdio.h>

int main(){
    return 0;
}

//Algorithm_1
int MaxSubseqSum1(int A[],int N)
{
    int ThisSum,MaxSum = 0;
    int i,j,k;
    for( i = 0; i < N; i++){
        for ( j = 0; j < N; j++){
            ThisSum = 0;

            for ( k = i; k <= j; k++)
                ThisSum+=A[k];

            if(ThisSum > MaxSum)
                MaxSum = ThisSum;
            
        }
        
    }
    return MaxSum;
}

//Algrithm_2
int MaxSubseqSum2(int A[], int N)
{
    int ThisSum, MaxSum = 0;
    int i, j;
     for( i = 0; i < N; i++){
         ThisSum = 0;
         for ( j = i; j < N; j++){
             ThisSum+=A[j];
             if (ThisSum>MaxSum)
                MaxSum = ThisSum;
         }
         
     }

}

//Algorithm_3 DivideAndConquer
int MaxSubseqSum3(int A[], int N)
{
    return DivideAndConquer(A,0,N-1);
}
int DivideAndConquer(int A[],int left,int right)
{
    int MaxLeftSum,MaxRightSum;
    int MaxLeftBorderSum,MaxRightBorderSum;
    int LeftBorderSum, RightBorderSum;
    int center,i;

    if (left == right)
    {
        if(A[left]>0)
            return A[left];
        else return 0;
        
    }

    center = (left+right)/2;
    MaxLeftSum = DivideAndConquer(A,left,center);
    MaxRightSum = DivideAndConquer(A,center+1,right);

    MaxLeftBorderSum = 0;
    LeftBorderSum = 0;
    for( i = center; i >= left; i--){
        LeftBorderSum+=A[i];
        if (LeftBorderSum>MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }
    
    MaxRightBorderSum=0;
    RightBorderSum = 0;
    for( i = center + 1; i <= right; i++ ){
        RightBorderSum+=A[i];
        if(RightBorderSum>MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }
    
    return MAX(MaxLeftSum,MaxRightSum,MaxLeftBorderSum+MaxRightBorderSum);
    
}
int MAX(int a, int b, int c)
{
    if( a > b )
        if( a > c ) 
            return a;
        else 
            return c;    
    else if( b > c )
        return b;
    else 
        return c;
}

//Algorithm_4 Online Porcessing
int MaxSubseqSum4(int A[], int N)
{
    int ThisSum,MaxSum;
    int i;
    ThisSum = MaxSum = 0;
    for( i = 0; i < N; i++){
        ThisSum+=A[i];
        if(ThisSum>MaxSum)
            MaxSum = ThisSum;
        else if(ThisSum<0)
            ThisSum = 0;
    }
    return MaxSum;
}