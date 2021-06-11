#include <stdio.h>
#include <stdlib.h>
int UnionArr[10002];
int N;

void uni(int a, int b)
{
    int roota = findroot(a);
    int rootb = findroot(b);
    if (UnionArr[roota] > UnionArr[rootb])
        UnionArr[roota] = rootb;

    else 
        UnionArr[rootb] = roota;
    //天才创意？nt测试！
    // {
    //     srand((unsigned)time(NULL));
    //     int random = rand() % 2;
    //     if (random)
    //         UnionArr[rootb] = roota;
    //     else
    //         UnionArr[roota] = rootb;
    // }
}

// int findroot(int a)
// {
//     while (UnionArr[a] > 0)
//         a = UnionArr[a];
//     return a;
// }
//路径压缩
int findroot(int a){
    if(UnionArr[a]>0){
        return UnionArr[a] = findroot(UnionArr[a]);
    }
    return a;
}

void findroots()
{
    int roots[N];
    int numbers = 0;
    for (int i = 1; i <= N; i++)
    {
        int tmproot = findroot(i);
        if (numbers == 0)
            roots[numbers++] = tmproot;
        else
        {
            int flag = 1;
            for (int i = 0; i < numbers; i++)
            {
                if (tmproot == roots[i])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
                roots[numbers++] = tmproot;
        }
    }

    if (numbers > 1)
    {
        printf("There are %d components.", numbers);
    }
    else
        printf("The network is connected.");
}
int main()
{
    char operation;
    int a, b;
    scanf("%d\n", &N);
    while (scanf("%c", &operation) != EOF && operation != 'S')
    {
        scanf("%d %d ", &a, &b);
        // printf("operation:%c a:%d b:%d\n",operation,a,b);
        if (operation == 'I')
        {
            uni(a, b);
        }
        else
        {
            if (findroot(a) != findroot(b))
            {
                // printf("comparing %d and %d\n",a,b);
                printf("no\n");
            }

            else
            {
                // printf("comparing %d and %d\n",a,b);
                printf("yes\n");
            }
        }
    }

    findroots();
    return 0;
}