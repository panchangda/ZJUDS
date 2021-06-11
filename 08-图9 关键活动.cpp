//Directed Acyclic Graph
//Compiler: C++(clang++) 
//g++ did not initialize the array -> segment fault
#include <stdio.h>
#include <string.h>
#include <queue>
#include <stack>

using namespace std;

int time[101][101];
int Indegree[101];
int Outdegree[101];
int EarliestTime[101];
int LatestTime[101];
int SpareTime[101][101];

int main()
{   
    memset(SpareTime,-1,sizeof(SpareTime));
    // printf("%d %d\n",sizeof(SpareTime),SpareTime[0][0]);
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= M; i++)
    {
        int start, end, t;
        scanf("%d %d %d", &start, &end, &t);
        time[start][end] = t;
    }

    //calculate indegrees of each vertex
    for (int i = 1; i <= N; i++)
    {
        int degrs = 0;
        for (int j = 1; j <= N; j++)
        {
            if (time[j][i])
                degrs++;
        }
        Indegree[i] = degrs;
    }

    //outdegrees
    for(int i =1 ;i<=N;i++){
        int degrs = 0;
        for(int j=1;j<=N;j++){
            if(time[i][j])
                degrs++;
        }
        Outdegree[i] = degrs;
    }

    //find the start points: indegrees=0 and push em into queue
    queue<int> q;
    int first_flag = 0;
    for (int i = 1; i <= N; i++)
    {   
        if (!Indegree[i])
        {
            q.push(i);
            first_flag = 1;
        }
    }
    if (!first_flag)
    {
        printf("0");
        return 0;
    }

    //bfs
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        for (int i = 1; i <= N; i++)
        {
            if (time[tmp][i])
            {
                if (--Indegree[i] == 0)
                    q.push(i);
                if (EarliestTime[i] < time[tmp][i] + EarliestTime[tmp])
                {
                    EarliestTime[i] = time[tmp][i] + EarliestTime[tmp];
                }
            }
        }
    }

    //if there's a circle?
    for (int i = 1; i <= N; i++)
    {
        if (Indegree[i] > 0)
        {
            printf("0");
            return 0;
        }
    }

    // find and output the biggest EarliestTime
    int max,max_idx;
    for (int i = 1; i <= N; i++)
    {    
        LatestTime[i] = 9999;
        if (EarliestTime[i] > max){
            max = EarliestTime[i];
            max_idx = i;
        } 
    }
    //as for the end, the earlist and the latest are same
    LatestTime[max_idx] = max;

    printf("%d\n", max);

    //find the end points: outdegress=0 and push em into queue
    for (int i = 1; i <= N; i++)
    {   
        if (!Outdegree[i])
        {
            q.push(i);  
        }
    }   

    //bfs
    while(!q.empty()){
        int tmp = q.front();
        q.pop();
        for (int i = 1; i <= N; i++)
        {
            if (time[i][tmp])
            {
                if (--Outdegree[i] == 0)
                    q.push(i);
                // '>=' -> 记录多条关键路径(完成时间相同)
                if (LatestTime[i] >= LatestTime[tmp] - time[i][tmp])
                {
                    LatestTime[i] = LatestTime[tmp] - time[i][tmp];
                    SpareTime[i][tmp] = LatestTime[tmp] - EarliestTime[i]-time[i][tmp];
                }
            }
        }
    }

    for(int i=1;i<=N;i++){
        for(int j=N;j>=1;j--){
            if(SpareTime[i][j]==0)
                printf("%d->%d\n", i, j);
        }
    }
    // for(int i=1;i<=N;i++){
    //     if(LatestTime[i]==EarliestTime[i])
    //         printf("%d->%d\n", i, j);
    // }

    // for(int i=1;i<=N;i++){
    //     printf("%d %d\n",EarliestTime[i],LatestTime[i]);
    // }


    // //start from the end, push key activities to stack
    // cannot deal with more than one end
    // stack<int> s;
    // while(end)
    // {
    //     s.push(end);
    //     end = path[end];
    // }

    // int tmp = s.top();
    // s.pop();
    // int next;
    // while (!s.empty())
    // {
    //     next = s.top();
    //     s.pop();
    //     printf("%d->%d\n", tmp, next);
    //     tmp = next;
    // }

    return 0;
}