#include <stdio.h>

int N, M;
int mtx[1001][1001];
int main()
{
    //intput
    scanf("%d %d", &N, &M);

    //initialize the matrix
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (i == j)
                mtx[i][j] = 0;
            else
                mtx[i][j] = 999999;
        }
    }

    //input to matrix
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        mtx[a][b] = mtx[b][a] = 1;
    }

    //Floyd
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
                if (mtx[i][j] > mtx[i][k] + mtx[k][j])
                    mtx[i][j] = mtx[i][k] + mtx[k][j];
        }
    }

    //output
    for (int i = 1; i <= N; i++)
    {
        int c = 0;
        for (int j = 1; j <= N; j++)
            if (mtx[i][j] <= 6)
                c++;
        // 错误计算方式:
        // c*100/N后直接作为int型取整后会丢失小数点后2位
        // printf("%d: %.2lf%%\n", i, (double)(c * 100 / N));

        // 正确计算方式:
        // 先将c转成double型再进行浮点数计算
        printf("%d: %.2lf%%\n", i, ((double)c * 100 / N));
    }
    return 0;
}