#include <stdio.h>
void MergeSort(int A[], int tmpA[], int start, int end,int mid)
{
    if (start >= end)
        return;
    int l_idx = start;
    int r_idx = mid + 1;
    int tmp_idx = start;
    while (l_idx <= mid && r_idx <= end)
        if (A[l_idx] <= A[r_idx])
            tmpA[tmp_idx++] = A[l_idx++];
        else
            tmpA[tmp_idx++] = A[r_idx++];
    while (l_idx <= mid)
        tmpA[tmp_idx++] = A[l_idx++];
    while (r_idx <= end)
        tmpA[tmp_idx++] = A[r_idx++];

    for (int i = start; i <= end; i++)
        A[i] = tmpA[i];
}
int min(int x, int y) { return x < y ? x : y; }
void Iterative_Merge_Driver(int A[], int tmpA[], int N, int limit)
{
    int length,start, end,mid ;
    for (length = 1; length < limit; length *= 2)
    {
        for (start = 0; start < N - 1; start += 2 * length)
        {   
            mid = min(start+length-1,N-1);
            end = min(start + 2 * length-1, N - 1);
            MergeSort(A, tmpA, start, end,mid);
        }
    }
}
void InserstionSort(int A[], int N)
{
    int tmp, j;
    for (int i = 1; i <= N; i++)
    {
        tmp = A[i];
        j = i - 1;
        while (A[j] >= tmp && j >= 0)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = tmp;
    }
}
int main()
{
    int N, i,j, iteration_time = 0;
    scanf("%d", &N);
    int InitialSeq[N], PrtSrtSeq[N];
    for (i = 0; i < N; i++)
        scanf("%d", &InitialSeq[i]);
    for (i = 0; i < N; i++)
        scanf("%d", &PrtSrtSeq[i]);
    
    for (i = 0; i < N - 1; i += 2)
        if (PrtSrtSeq[i] <= PrtSrtSeq[i + 1])
            continue;
        else
            break;

    //i will be N(N is even)/N-1(N is odd)
    if(i == N || i == N - 1)
    {
        printf("Merge Sort\n");
        while (iteration_time<N-1&&PrtSrtSeq[iteration_time] < PrtSrtSeq[iteration_time + 1])
            iteration_time++;
        iteration_time++;
        // printf("iteTime is %d\n",iteration_time);

        /*
        testpoint6:检查片段长度 以第一段的itetime作为初始迭代值进行后续的检查
        若后续有不符合的则itetime/=2重新进行迭代
        */
        int flag = 0;
        while(iteration_time>=2){
            for(j=iteration_time;j<N-1;j+=iteration_time){
                if(j+iteration_time>N-2){
                    while(j<N-1){
                        if(!(PrtSrtSeq[j] < PrtSrtSeq[j + 1])){
                            flag = 1; 
                        }
                           
                        j++;
                    }
                    break;
                }
                else{
                    int k = 0;
                    while(k<iteration_time){
                        if(!(PrtSrtSeq[j] < PrtSrtSeq[j + 1])){
                            flag = 1;
                            break;
                        }
                        k++;
                    }
                    if(flag)
                        break;
                }
                
            } 
               
            if(flag){
                iteration_time/=2;
                flag = 0;
            }
            else
                break;        
        }
        iteration_time*=2;
        // printf("iteTime is %d\n",iteration_time);
        int tmpA[N];
        Iterative_Merge_Driver(InitialSeq, tmpA, N, iteration_time/4);
        /*
        testpoint 6:
        6
        2 1 6 5 4 3
        1 2 5 6 3 4
        OUTPUT
        CORRECT: 1 2 5 6 3 4
        WRONG: 1 2 3 4 5 6
        */
        for(i=0;i<N-1;i++){
            if(InitialSeq[i]==PrtSrtSeq[i])
                continue;
            else{
                Iterative_Merge_Driver(InitialSeq, tmpA, N, iteration_time);
                break;
            }
        } 
            
        for (i = 0; i < N - 1; i++)
            printf("%d ", InitialSeq[i]);
        printf("%d", InitialSeq[N - 1]);
    }

    //testcase 4:PrtSrtSeq[iteration_time] <= PrtSrtSeq[iteration_time + 1]
    //if '>=' -> '>' then fails
    else
    {
        printf("Insertion Sort\n");
        while (iteration_time<N-1&&PrtSrtSeq[iteration_time] <= PrtSrtSeq[iteration_time + 1])
            iteration_time++;
        iteration_time++;
        
        InserstionSort(InitialSeq, iteration_time);
        for (i = 0; i < N - 1; i++)
            printf("%d ", InitialSeq[i]);
        printf("%d", InitialSeq[N - 1]);
    }
    return 0;
}