//Directed Acyclic Graph
#include<stdio.h>
#include<queue>

using namespace std;

int Indegree[100];
int time[100][100];
int completion_time[100];

int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    for(int i=0;i<M;i++){
        int start,end,t;
        scanf("%d %d %d",&start,&end,&t);
        time[start][end]=t;
    }

    //calculate degrees of each vertex
    for(int i=0;i<N;i++){
        int degrs=0;
        for(int j=0;j<N;j++){
            if(time[j][i])
                degrs++;
        }
        Indegree[i]=degrs;
    }

    //find the start points and push em into queue
    queue<int>q;
    int startpoints = 0;
    for(int i=0;i<N;i++){
        if(!Indegree[i]){
            q.push(i);
            startpoints = 1;
        }
    }
    
    //if startpoints which indegree is 0 exist
    if(!startpoints){
        printf("Impossible");
        return 0;
    }

    //bfs 
    while(!q.empty()){
        int tmp = q.front();
        q.pop();
        Indegree[tmp]=-1;
        for(int i=0;i<N;i++){
            if(time[tmp][i]){
                Indegree[i]--;
                if(Indegree[i]==0)
                    q.push(i);
                //completion_time:其他点到i的所有完成时间的最大值
                //其他点到i的完成时间:其他点的completion_time+tmp到i的时间
                completion_time[i]
                =completion_time[i]<time[tmp][i]+completion_time[tmp]
                ?time[tmp][i]+completion_time[tmp]
                :completion_time[i];
            }
        }
    }    

    // 错误push方法 无法通过测试点4
    // 原因：会将初始入度为0的起点多次添加导致后续计算错误
    // for(int i=0;i<N;i++){
    //     if(Indegree[i]==0)
    //         q.push(i);
    // }

    //if there's a circle?
    for(int i=0;i<N;i++){
        if(Indegree[i]>0){
            printf("Impossible");
            return 0;
        }
    }

    //output the biggest completion_time
    int max = 0;
    for(int i=0;i<N;i++){
        if(completion_time[i]>max)
            max = completion_time[i];
    }
    printf("%d",max);

    return 0;
}