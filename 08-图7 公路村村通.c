//minimum spanning tree
//Prim alg
#include<stdio.h>
#define INF 9999
int cost[1001][1001];
int N,M;
int collected[1001];
int res[1001];
int sum;

void prim(int root)
{
    collected[root] = 1;

    for(int i=1;i<=N;i++)
        res[i]=cost[root][i];

    while (1)
    {
        int min_dis = INF;
        int min_v = 0;
        for (int i = 1; i <= N; i++)
        {   
            if (res[i] < min_dis && (!collected[i]))
            {
                min_dis = res[i];
                min_v = i;
            }
        }
        
        if(min_dis == INF)
            break;

        sum+=min_dis;
        collected[min_v] = 1;

        res[min_v] = min_dis;

        for (int i = 1; i <= N; i++)
        {
            if (cost[min_v][i] < res[i]&& !collected[i])
            {   
                res[i] = cost[min_v][i];           
            }
        }
    }
}
int main(){
    scanf("%d %d",&N,&M);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            cost[i][j]=INF;

    for(int i=0;i<M;i++){
        int a,b,weight;
        scanf("%d %d %d",&a,&b,&weight);
        cost[a][b]=cost[b][a]=weight;
    }

    prim(1);

    int flag = 1;
    for(int i=1;i<=N;i++)
        if(!collected[i])
            flag = 0;
    if(flag){
        printf("%d",sum);
    }
    else    
        printf("-1");
    return 0;
}