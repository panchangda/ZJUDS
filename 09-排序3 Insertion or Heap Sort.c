#include<stdio.h>
#include<string.h>
void InsertionSort(int* A,int N){
    int tmp,i,j;
    for(i=1;i<=N;i++){
        tmp= A[i];
        for(j=i-1;j>=0;j--){
            if(A[j]>tmp){
                A[j+1] = A[j];
            }
            else
                break;
        }
        A[j+1] = tmp; 
    }
}
void swap(int* x,int* y){
    int tmp = *x;
    *x = *y;
    *y = tmp; 
}
void heapify(int* A,int N,int root){
    int largest = root;
    int l = 2*root+1;
    int r = 2*root+2;
    if(l<N&&A[l]>A[largest])
        largest = l;
    if(r<N&&A[r]>A[largest])
        largest = r;
    if(largest!=root){
        swap(&A[largest],&A[root]);
        heapify(A,N,largest);
    }
}
void BuildMaxHeap(int *A,int N){
    for(int i=N/2-1;i>=0;i--){
        heapify(A,N,i);
    }
}
void HeapJustify(int* A,int N,int ite_time){
    //move the max to the end
    swap(&A[0],&A[N-ite_time]);
    heapify(A,N-ite_time,0);
}
int main(){
    int N;
    scanf("%d",&N);
    int OrgSeq[N],PrtSrtSeq[N],SeqForIns[N],SeqForHp[N];
    for(int i=0;i<N;i++)
        scanf("%d",&OrgSeq[i]);
    for(int i=0;i<N;i++)
        scanf("%d",&PrtSrtSeq[i]);
    
    memcpy(SeqForIns,OrgSeq,N*sizeof(int));
    //build max heap
    memcpy(SeqForHp,OrgSeq,N*sizeof(int));
    BuildMaxHeap(SeqForHp,N);

    for(int i=1;i<=N;i++){
        InsertionSort(SeqForIns,i);
        HeapJustify(SeqForHp,N,i);
        // for(int k=0;k<N-1;k++)
        //         printf("%d ",SeqForHp[k]);
        //     printf("%d\n",SeqForHp[N-1]);
        if(!memcmp(PrtSrtSeq,SeqForIns,N*sizeof(int))){
            printf("Insertion Sort\n");
            //one more time
            InsertionSort(SeqForIns,i+1);
            //output
            for(int k=0;k<N-1;k++)
                printf("%d ",SeqForIns[k]);
            printf("%d",SeqForIns[N-1]);
            break;
        }
        if(!memcmp(PrtSrtSeq,SeqForHp,N*sizeof(int))){
            printf("Heap Sort\n");
            HeapJustify(SeqForHp,N,i+1);
            for(int k=0;k<N-1;k++)  
                printf("%d ",SeqForHp[k]);
            printf("%d",SeqForHp[N-1]);
            break;
        }
    }
    return 0;
}