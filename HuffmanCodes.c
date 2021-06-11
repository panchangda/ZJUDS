#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree_node node;
typedef struct tree_node *ptr_to_node;
typedef struct tree_node
{
    int assigned;
    int weight;
    ptr_to_node lchild;
    ptr_to_node rchild;
};

int fq[63];
int h[63];


void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void heapify(int N, int root)
{
    int smallest = root;
    int l = root * 2 + 1;
    int r = root * 2 + 2;
    if (l < N && h[l] < h[smallest])
    {
        smallest = l;
    }
    if (r < N && h[r] < h[smallest])
    {
        smallest = r;
    }
    if (smallest != root)
    {
        swap(&h[smallest], &h[root]);
        heapify(N, smallest);
    }
}

void BuildMinHeap(int N)
{
    int idx = 0;
    for (int i = 0; i < 63; i++)
    {
        if (fq[i])
        {
            h[idx++] = fq[i];
        }
    }

    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(N, i);

    // for(int i=0;i<N;i++){
    //     printf("%d ",h[i]);
    // }
}

void justify(int N)
{
    swap(&h[0], &h[N]);
    heapify(N, 0);
}

int WPL_WITHOUT_BUILDINGTREE(int N){
    BuildMinHeap(N);
    int count = N;
    int wpl = 0;
    int min1,min2;
    while(count>1){
        min1 = h[0];
        justify(--count);
        min2 = h[0];
        wpl+=(min1+min2);
        h[0] = min1+min2;
        heapify(count,0);
        // printf("%d %d\n",min1,min2);
    }
    return wpl;
}

int IsPrefix(ptr_to_node head, char *code)
{
    ptr_to_node now = head;
    ptr_to_node tmp = NULL;
    for (int i = 0; i < strlen(code); i++)
    {
        if (*(code + i) == '0')
        {
            if (!now->lchild)
            {
                tmp = malloc(sizeof(node));
                tmp->assigned = 0;
                tmp->lchild = tmp->rchild = NULL;
                now->lchild = tmp;
                now = now->lchild;
            }
            else
            {
                now = now->lchild;
                if (now->assigned)
                    return 0;
            }
        }
        else
        {
            if (!now->rchild)
            {
                tmp = malloc(sizeof(struct tree_node));
                tmp->assigned = 0;
                tmp->lchild = tmp->rchild = NULL;
                now->rchild = tmp;
                now = now->rchild;
            }
            else
            {
                now = now->rchild;
                if (now->assigned)
                    return 0;
            }
        }
    }

    if (now->lchild || now->rchild)
        return 0;

    return 1;
}

int WPL_Tree(ptr_to_node node, int depth)
{
    if (!node->lchild && !node->rchild)
        return node->weight * depth;
    else
        //notice +1 do not use ++!!!
        return (WPL_Tree(node->lchild, depth + 1) 
        + WPL_Tree(node->rchild, depth + 1));
}

int WPL_Node(char c, int length)
{
    if (c >= '0' && c <= '9')
        return fq[c - '0'] * length;
    //A-Z
    else if (c >= 'A' && c <= 'Z')
        // printf("wpl_node:%c %d\n",c,length);
        return fq[c - 'A' + 10] * length;
    //a-z
    else if (c >= 'a' && c <= 'z')
        return fq[c - 'a' + 36] * length;
    //_
    else
        return fq[62] * length;
}

int main()
{
    memset(fq, 0, sizeof(fq));
    int N, M, tmp;
    char c;
    char code[64];
    //need to have "%d\n"
    //input buffer get a space or /n first
    scanf("%d\n", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%c %d ", &c, &tmp);
        // printf("%d put at %c\n",tmp,c);
        //0-9
        if (c >= '0' && c <= '9')
            fq[c - '0'] = tmp;
        //A-Z
        else if (c >= 'A' && c <= 'Z')
            fq[c - 'A' + 10] = tmp;
        //a-z
        else if (c >= 'a' && c <= 'z')
            fq[c - 'a' + 36] = tmp;
        //_
        else
            fq[62] = tmp;
    }

    // ptr_to_node head_node = BuildHuffmanTree(N);
    // int wpl_min = WPL_Tree(head_node, 0);
    int wpl_min = WPL_WITHOUT_BUILDINGTREE(N);
    // printf("minwpl: %d\n",wpl_min);

    for (scanf("%d\n", &M); M > 0; M--)
    {
        int wpl = 0;
        int isPrefix = 1;
        ptr_to_node head = malloc(sizeof(node));
        head->assigned = 0;
        head->lchild = head->rchild = NULL;

        for (int i = 0; i < N; i++)
        {
            scanf("%c %s ", &c, code);
            // printf("%c %s\n",c,code);
            if (isPrefix && !IsPrefix(head, code))
            {
                isPrefix = 0;
            }
            wpl += WPL_Node(c, strlen(code));
        }

        // printf("wpl: %d pfx: %d\n", wpl, isPrefix);

        if (isPrefix && wpl == wpl_min)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}




//
//
//fucking idiot shit codes:
//trying to build tree without storing struct into heap
//
//

/*
ptr_to_node BuildHuffmanTree(int N)
{

    BuildMinHeap(N);

    int min, count = N;
    ptr_to_node new_root = NULL;
    ptr_to_node last_root = NULL;
    ptr_to_node new_child = NULL;

    last_root = malloc(sizeof(node));
    last_root->lchild = last_root->rchild = NULL;
    last_root->weight = h[0];
    justify(--count);

    while (count > 0)
    {   
        new_child = malloc(sizeof(node));
        new_child->lchild = new_child->rchild = NULL;
        new_child->weight = h[0];
        justify(--count);
        // for(int i=0;i<N;i++){
        //     printf("%d ",h[i]);
        // }
        // putchar('\n');
        
        //test
        if(h[0]+new_child->weight<last_root->weight){
            ptr_to_node new_child_2 = malloc(sizeof(node));
            new_child_2->lchild = new_child_2->rchild = NULL;
            new_child_2->weight = h[0];
            justify(--count);
            ptr_to_node new_child_root = malloc(sizeof(node));
            new_child_root->lchild = new_child;
            new_child_root->rchild = new_child_2;
            new_child = new_child_root;
        }
        new_root = malloc(sizeof(node));
        new_root->lchild = last_root;
        new_root->rchild = new_child;
        new_root->weight = 0;
        
        last_root = new_root;
    }

    return last_root;
}
*/