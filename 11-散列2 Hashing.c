#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXTABLESIZE 100000

typedef struct hashtable
{
    int tableSize;
    int *list;
} * HashTable;

int NextPrime(int MSize)
{
    int i, p = (MSize % 2) ? MSize : MSize + 1;
    //测试点2 最小值
    if(p==1)
        return 2;
    while (p < MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--){
            if (!(p % i))
                break;
        }
        if (i == 2)
            break;
        else
            p += 2;
    }

    return p;
}
HashTable CreateHashTable(int MSize)
{
    int tableSize = NextPrime(MSize);
    HashTable H = (HashTable)malloc(sizeof(struct hashtable));
    H->list = (int *)malloc(tableSize * sizeof(int));
    H->tableSize = tableSize;
    for (int i = 0; i < tableSize; i++)
    {
        H->list[i] = 0;
    }
    return H;
}
int Hash(int key, int tableSize)
{
    return key % tableSize;
}
int Insert(int tmp, HashTable H)
{

    int position, ite = 0;
    while (ite < H->tableSize / 2)
    {
        position = Hash(tmp + ite * ite, H->tableSize);
        if (!(H->list[position]))
        {
            H->list[position] = tmp;
            return position;
        }
        ite++;
    }
    return -1;
}
int main()
{
    int MSize, N, tmp, result;
    scanf("%d %d", &MSize, &N);
    HashTable H = CreateHashTable(MSize);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &tmp);
        result = Insert(tmp, H);

        //deal with the output format
        if (i > 0)
            putchar(' ');

        if (result == -1)
            printf("-");
        else
            printf("%d", result);
    }

    return 0;
}