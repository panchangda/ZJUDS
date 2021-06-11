#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<string.h>

#define MAXTABLESIZE 21474836472

typedef char AccountNumber[11];
typedef char Password[17];
typedef struct Node *PtrToNode;

typedef struct Node
{
    AccountNumber an;
    Password pw;
    PtrToNode next;
};

typedef struct HashNode *HashTable;
typedef struct HashNode
{
    int tableSize;
    PtrToNode heads;
};

int NextPrim(int N)
{
    int i, p = (N % 2) ? N + 2 : N + 1;
    while (p < MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))
                break;
        if (i == 2)
            break;
        else
            p += 2;
    }
    return p;
}

int Hash(AccountNumber an, int tableSize)
{
    return atoi(an + 3) % tableSize;
}


PtrToNode Find(HashTable H, AccountNumber an)
{
    PtrToNode P;
    int pos;
    pos = Hash(an, H->tableSize);
    P = H->heads[pos].next;

    //find p if p already exists
    while (P && strcmp(P->an, an))
        P = P->next;

    return P;
}

int Login(HashTable H, AccountNumber an, Password pw)
{
    PtrToNode P, newNode;
    int pos;
    P = Find(H, an);
    //if p does not exist
    if (!P)
    {
        return 4;
    }
    //p exists and pw correct
    else if(!strcmp(P->pw,pw))
    {   
        return 3;
    }
    //p exists and wrong password
    else{
        return 5;
    }
}

int Register(HashTable H, AccountNumber an,Password pw)
{
    PtrToNode P, newNode;
    int pos;
    P = Find(H, an);
    //if p does not exist 
    //register a new one
    if (!P)
    {
        newNode = (PtrToNode)malloc(sizeof(struct Node));
        strcpy(newNode->an, an);
        strcpy(newNode->pw, pw);
        int pos = Hash(an, H->tableSize);
        newNode->next = H->heads[pos].next;
        H->heads[pos].next = newNode;
        return 1;
    }
    //p already exists
    else
    {   
        return 2;
    }
}

HashTable CreateHashTable(int tableSize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct HashNode));
    H->tableSize = NextPrim(tableSize);
    // printf("%d\n",H->tableSize);
    H->heads = (PtrToNode)malloc(H->tableSize * sizeof(struct Node));
    for (i = 0; i < H->tableSize; i++)
    {
        H->heads[i].an[0] = '\0';
        H->heads[i].pw[0] = '\0';
        H->heads[i].next = NULL;
    }
    return H;
}
int main()
{
    int N,result;
    char ope;
    AccountNumber an;
    Password pw;
    scanf("%d",&N);

    HashTable H = CreateHashTable(N);
    
    for (; N > 0; N--)
    {   
        //%s后的空格抑或是%c前的空格--永远的痛!
        scanf(" %c %s %s", &ope, an, pw);
        // printf("scanf in : %c %s %s\n",ope,an,pw);
        if (ope=='L')
        {   
            result = Login(H,an,pw);
        }
        else
        {
            result = Register(H,an,pw);
        }
        switch(result){
            case 1:printf("New: OK\n");break;
            case 2:printf("ERROR: Exist\n");break;
            case 3:printf("Login: OK\n");break;
            case 4:printf("ERROR: Not Exist\n");break;
            case 5:printf("ERROR: Wrong PW\n");break;
            default:printf("!ERROR!\n");break;
        }
    }
    return 0;
}