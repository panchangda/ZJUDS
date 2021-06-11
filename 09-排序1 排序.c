/*实现了所有的常用排序算法*/
#include <stdio.h>
#include <stdlib.h>

int A[100000];

void swap(int *xp, int *yp)
{
    int tmp = *xp;
    *xp = *yp;
    *yp = tmp;
}
void BubbleSort(int *A, int N)
{
    int i, j;
    for (i = 0; i < N - 1; i++)
    {
        for (j = 0; j < N - 1; j++)
            if (A[j] < A[i])
                swap(&A[j], &A[i]);
    }
}
void BubblSort_R(int *A, int N)
{
    if (N == 1)
        return;
    for (int i = 0; i < N - 1; i++)
        if (A[i] > A[i + 1])
            swap(&A[i], &A[i + 1]);
    //already move the largest to the end
    //so the N=N-1
    BubbleSort(A, N - 1);
}
void InsertionSort(int *A, int N)
{
    int i, j, tmp;
    for (i = 1; i < N; i++)
    {
        tmp = A[i];
        while (j >= 0 && A[j] > tmp)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = tmp;
    }
}
void InsertionSort_R(int *A, int N)
{
    if(N==1)
        return;
    InsertionSort_R(A,N-1);
    int tmp = A[N-1];
    int j = N-2;
    while(j>=0&&tmp<A[j]){
        A[j+1] = A[j];
        j--;
    }
    A[j+1] = tmp;
        
}
void SelectionSort(int *A, int N)
{
    int i, j, min_idx;
    for (i = 0; i < N - 1; i++)
    {
        min_idx = i;
        for (j = i; j < N; j++)
        {
            if (A[j] < A[min_idx])
                min_idx = j;
        }
        swap(&A[i], &A[min_idx]);
    }
}
/* Shell Sort */
// ShellSort with Sedegewick 增量序列 
void ShellSort(int A[], int N)
{
    
    int Si, GAP, P, i;
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    for (Si = 0; Sedgewick[Si] >= N; Si++)
        ;
    for (GAP = Sedgewick[Si]; GAP > 0; Si++)
    {
        for (P = GAP; P < N; P++)
        {
            int tmp = A[P];
            for (i = P; i >= GAP && A[i - GAP] > tmp; i -= GAP)
            {
                A[i] = A[i - GAP];
            }
            A[i] = tmp;
        }
    }
}

/* Heap Sort*/
/* Up -> Down */
void heapify(int *A, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && A[l] > A[largest])
        largest = l;
    if (r < n && A[r] > A[largest])
        largest = r;
    if (largest != i)
    {
        swap(&A[i], &A[largest]);
        heapify(A, n, largest);
    }
}

void HeapSort(int *A, int N)
{
    //build heap from 倒数第二层
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(A, N, i);
    //move the largest to the last node
    //and ignore it -> N--
    for (int i = N - 1; i > 0; i--)
    {
        swap(&A[0], &A[i]);
        heapify(A, i, 0);
    }
}

/* Merge Sort */
//L:leftstart R:RightStart 
void Merge(int *A, int *tmpA, int L, int R, int end)
{
    int mid = end - R + 1;
    int length = end - L + 1;
    int idx = L;
    while (L <= mid && R <= end)
        if (A[L] <= A[R])
            tmpA[idx++] = A[L++];
        else
            tmpA[idx++] = A[R++];
    while (L <= mid)
        tmpA[idx++] = A[L++];
    while (R <= end)
        tmpA[idx++] = A[R++];

    for (int i = 0; i < length; i++, end--)
        A[end] = tmpA[end];
}
//VERSION = recursion;
void MergeSort_R(int *A, int *tmp, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort_R(A, tmp, start, mid);
        MergeSort_R(A, tmp, mid + 1, end);
        Merge(A, tmp, start, mid, end);
    }
}
void MergeSort_Driver_R(int *A, int N)
{
    int *tmpA = malloc(N * sizeof(int));
    if (tmpA)
    {
        MergeSort_R(A, tmpA, 0, N - 1);
        free(tmpA);
    }
    else //malloc error
        ;
}
//VERSION = iteration
void MergeSort_I(int *A, int *tmpA, int N, int length)
{
    int i;
    for (i = 0; i <= N - 2 * length; i += 2 * length)
    {
        /*
         *** 
         Merge without copying tmpA to A in the end 
         ***
         */
        Merge(A, tmpA, i, i + length, i + 2 * length - 1);
    }
    if (N - i > length)
    {
        Merge(A, tmpA, i, i + length, N - 1);
    }
    else
        for (int j = i; i < N; j++)
            tmpA[j++] = A[j++];
}
void MergeSort_Driver_I(int *A, int N)
{
    int length = 1;
    int *tmpA = malloc(N * sizeof(int));
    if (tmpA)
    {
        while (length < N)
        {
            MergeSort_I(A, tmpA, N, length);
            length *= 2;
            MergeSort_I(A, tmpA, N, length);
            length *= 2;
        }
        free(tmpA);
    }
    else //  Error
        ;
}

/* 
//version = recursive
void MergeSort_R(int* A, int* tmpA, int start, int end)
{
    if (start >= end)
        return;
    int mid = (start + end) / 2;
    int idxL = start;
    int idxR = mid+1;
    int idxT = start;
    //int mid = (R-L)>>1 + L;

    //resursive call
    MergeSort_R(A, tmpA, idxL, mid);
    MergeSort_R(A, tmpA, idxR, end);

    //Merge Operation
    while(idxL<=mid&&idxR<=end)
    if(A[idxL]<=A[idxR])
        tmpA[idxT] = A[idxL++];
    else
        tmpA[idxT] = A[idxR++];
    while(idxL<=mid)
        tmpA[idxT++] = A[idxL++];
    while(idxR<=end)
        tmpA[idxT++] = A[idxR++];
    for(;start<end;start++)
        A[start] = tmpA[start];
}
void MergeSort_Entry(int *A, int N)
{
    int *tmpA = malloc(N * sizeof(int));
    if (tmpA)
    {
        MergeSort_I(A,tmpA,N);
        //MergeSort_R(A, tmpA, 0, N-1);
        free(tmpA);
    }
    else 
    //Error
    ;
}
*/

/* QuickSort */
//VERSION = ZJU.DS
int Median(int* A,int left,int right){
    int mid = (left+right)/2 ;
    if(A[left]>A[mid])
        swap(&A[left],&A[mid]);
    if(A[left]>A[right])
        swap(&A[left],&A[right]);
    if(A[mid]>A[right])
        swap(&A[mid],&A[right]);
    /*
     * NOW: A[left] <= A[mid] <= A[right] *
     */
    swap(&A[mid],&A[right-1]);

    return A[right-1];
}
void QuickSort(int* A,int left,int right){
    int pivot,cutoff,low,high;

    if(cutoff<=right-left){
        pivot = Median(A,left,right);
        low = left;high = right-2;
        while(1){
            while(A[low++]<pivot);
            while(A[right--]>pivot);
            if(low<high)
                swap(&A[low],&A[right]);
            else    
                break;
        }
        swap(&A[low],&A[right-1]);
        QuickSort(A,left,low-1);
        QuickSort(A,low+1,right);
    }
    else{
        //*A+left*
        InsertionSort(A+left,right-left+1);
    }
}
//driver
void QSort(int* A,int N){
    QuickSort(A,0,N-1);
}

//VERSION=GEEKFORGEEKS
int partition(int* A,int left,int right){
    int pivot = A[right];
    int smaller = left;
    for(int j=left;j<right;j++){
        if(A[j]<pivot){
            swap(&A[j],&A[smaller]);
            smaller++;
        }
    }
    swap(&A[right],&A[smaller]);
    return smaller;
}
void QuickSort2(int* A,int left,int right){
    if(left>=right)
        return;
    int pivot_position = partition(A,left,right);
    QuickSort2(A,left,pivot_position-1);
    QuickSort2(A,pivot_position+1,right);
}
//driver
void QSort1(int* A,int N){
    QuickSort2(A,0,N-1);
}

/*Bucket Sort  ==> Radix Sort*/

int main(){
    int N;
    scanf("%d",&N);
    for(int i=0;i<N;i++)
        scanf("%d",A+i);
    HeapSort(A,N);
    for(int i=0;i<N;i++){
        if(i)
            putchar(' ');
        printf("%d",*(A+i));
    }
        
    return 0;
}