/* alg from the brilliant jyj */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int cmp(int* a,int *b){
    return *a-*b;
}

int Find(int key,int N,int* hash){
    int pos = key%N;
    while(hash[pos]){
        pos++;
        if(pos==N)
            pos = 0;
    }
    // printf("find pos:%d",pos);
    return pos;
}

int main(){
    int N;
    scanf("%d",&N);
    int result[N],sorted[N],hash[N];
    for(int i=0;i<N;i++){
        scanf("%d",&result[i]);
    }
    for(int i=0;i<N;i++)
        hash[i] = 0;
    // putchar('\n');
    // for(int i=0;i<N;i++)
    //     printf("%d ",result[i]);
    memcpy(sorted,result,4*N);

    // for(int i=0;i<N;i++)
    //     printf("%d ",sorted[i]);

    qsort(sorted,N,4,cmp);
    // for(int i=0;i<N;i++)
    //     printf("%d ",sorted[i]);

    int empty = 0;
    int count = 0;
    int first = 1;
    for(int i=0;i<N;i++)
        if(sorted[i]<0)
            empty++;
    
    while(count!=N-empty){
        for(int i=0;i<N;i++){
            if(sorted[i]>=0&&result[Find(sorted[i],N,hash)]==sorted[i]){
                if(first){
                    printf("%d",sorted[i]);
                    first = 0;
                }
                else
                    printf(" %d",sorted[i]);
                
                hash[Find(sorted[i],N,hash)] = sorted[i];
                sorted[i] = -1;
                count++;
                break;
            }
        }
    }


    return 0;
}