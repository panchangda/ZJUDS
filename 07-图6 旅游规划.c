#include <stdio.h>
int dis[500][500];
int fees[500][500];
int res_dis[500];
int res_fee[500];
int confirmed[500];
int N, M, S, D;

void dijkstra()
{
    confirmed[S] = 1;
    res_dis[S] = 501;
    res_fee[S] = 0;
    while (1)
    {
        int min_dis = 501;
        int min_v = 0;
        for (int i = 0; i < N; i++)
        {   
            if (dis[S][i] < min_dis && (!confirmed[i]))
            {
                min_dis = dis[S][i];
                min_v = i;
            }
        }
        if (min_dis == 501)
            break;
        confirmed[min_v] = 1;
        res_dis[min_v] = min_dis;
        res_fee[min_v] = fees[S][min_v];
        for (int i = 0; i < N; i++)
        {
            if (dis[min_v][i] < 501 && !confirmed[i]  
            && dis[min_v][i] + min_dis <= dis[S][i])
            {   
                if(dis[min_v][i] + min_dis == dis[S][i]
                && fees[min_v][i]+fees[S][min_v]>fees[S][i])
                    continue;
                dis[S][i] = dis[min_v][i] + min_dis;
                fees[S][i] = fees[min_v][i] + fees[S][min_v];

            }
        }
    }
}

int main()
{
    scanf("%d %d %d %d", &N, &M, &S, &D);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            dis[i][j] = 501;
        }
                
    
    for (int i = 0; i < M; i++)
    {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        dis[a][b] = dis[b][a] = c;
        fees[a][b] = fees[b][a] = d;
    }

    dijkstra();

    printf("%d %d",res_dis[D],res_fee[D]);
    
}