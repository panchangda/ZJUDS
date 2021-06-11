#include <stdio.h>
/*
空间换时间
*/
int A[100000],position[100000];
int N,count=0;
int Sorted(){
    int cnt = 0;
    for(int i=0;i<N;i++)
        if(A[i]!=i){
            cnt++;
        }
    return cnt;
}
int main()
{   
    int pos=-1;
    int NotSort,k=1;
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        int tmp;
        scanf("%d", &tmp);
        A[tmp] = i; 
    }    

    NotSort = Sorted();

    while(NotSort){
        if(A[0]==0){
            for(;k<N;k++)
                if(A[k]!=k){
                    A[0] = A[k];
                    A[k] = 0;
                    count++;
                    NotSort++;
                    // printf("swap 0 %d \n",k);
                    break;
                }           
        }
        else{
            pos = A[0];
            A[0] = A[pos];
            A[pos] = pos;
            count++;
            NotSort--;
            if(A[0]==0)
                NotSort--;
            // printf("swap 0 %d \n",pos);
            // printf("%d\n",NotSort);
        }
    }
    printf("%d",count);
}