#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KEYLENGTH 11
#define MAXTABLESIZE 100000

typedef struct Node *PtrToNode;
typedef struct Node *Position;
typedef struct Node *List;
struct Node
{
    char data[12];
    PtrToNode next;
    int count;
};

typedef struct TblNode *HashTable;
struct TblNode
{
    int tablesize;
    PtrToNode heads;
};

int NextPrim(int N)
{
    int i, p = (N % 2) ? N + 2 : N + 1;
    while (p < MAXTABLESIZE)
    {   
        //此处for中的int错误 但是仍然AC了
        //下文中需要判断i来决定是否跳出循环
        //此处使用int i会导致每次tablesize都为最大值
        for (int i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))
                break;
        if (i == 2)
            break;
        else
            p += 2;
    }
    return p;
}
Position Find(HashTable H, char key[12])
{
    Position P;
    int pos;
    pos = Hash(atoi(key + 11 - 5), H->tablesize);
    P = H->heads[pos].next;
    //find p if p already exists
    while (P && strcmp(P->data, key))
        P = P->next;
    return P;
}

int Insert(HashTable H, char *key)
{
    Position P, newNode;
    int pos;
    P = Find(H, key);
    //if p does not exist 
    //create a new node and insert it to the first position
    if (!P)
    {
        newNode = (Position)malloc(sizeof(struct Node));
        strcpy(newNode->data, key);
        newNode->count = 1;
        pos = Hash(atoi(key + 11 - 5), H->tablesize);
        newNode->next = H->heads[pos].next;
        H->heads[pos].next = newNode;
        return 1;
    }
    else
    {
        P->count++;
        return 0;
    }
}

int Hash(int key, int tablesize)
{
    return key % tablesize;
}

HashTable CreateTable(int tablesize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->tablesize = NextPrim(tablesize);
    H->heads = malloc(H->tablesize * sizeof(struct Node));
    for (i = 0; i < H->tablesize; i++)
    {
        H->heads[i].data[0] = '\0';
        H->heads[i].next = NULL;
        H->heads[i].count = 0;
    }
    return H;
}

void DestroyTable(HashTable H)
{
    int i;
    Position P, tmp;
    for (i = 0; i < H->tablesize; i++)
    {
        P = H->heads[i].next;
        while (P)
        {
            tmp = P->next;
            free(P);
            P = tmp;
        }
    }
    free(H->heads);
    free(H);
}
void ScanAndOutput(HashTable H)
{
    int max = 0;
    int same = 0;
    char phonenmb[12];
    phonenmb[0] = '\0';
    PtrToNode tmpNode;
    for (int i = 0; i < H->tablesize; i++)
    {
        tmpNode = H->heads[i].next;
        while (tmpNode)
        {
            if (tmpNode->count > max)
            {
                max = tmpNode->count;
                strcpy(phonenmb, tmpNode->data);
                same = 0;
            }
            else if (tmpNode->count == max)
            {
                if (strcmp(phonenmb, tmpNode->data) > 0)
                    strcpy(phonenmb, tmpNode->data);
                same++;
            }
            tmpNode = tmpNode->next;
        }
    }

    if (!same)
    {
        printf("%s %d", phonenmb, max);
    }
    else
    {
        printf("%s %d %d", phonenmb, max, same + 1);
    }
}
int main()
{
    int N;
    char Call[12], Recv[12];
    scanf("%d", &N);
    HashTable H = CreateTable(N * 2);
    for (int i = 0; i < N; i++)
    {
        scanf("%s %s", Call, Recv);
        Insert(H, Call);
        Insert(H, Recv);
    }
    ScanAndOutput(H);
    DestroyTable(H);
    return 0;
}