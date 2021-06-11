//吃一堑长一智之十分钟能搞定的题硬是de了3小时bug
/*
1. 认真看错误提示并尝试理解 说了是段错误：地址越界数组溢出等就应该先关注这块
而非是自己臆想的scanf有问题
2. 时刻注意i和j，再也不要犯下面这种低级错误了！
for(int i=0;i<=N;i++){
        for(int j=0;i<=N;j++)
*/

#include<stdio.h>
#include<stdlib.h>
int distance[101][101];
int MIN[101];

int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            if(i==j)
                distance[i][j]=0;
            else 
                distance[i][j]=101;
        }
    }
        
    for(int i=0;i<M;i++){
        int a,b,length;
        scanf("%d %d %d",&a,&b,&length);
        distance[a][b]=distance[b][a]=length;
    }

    //Floyd
    for(int k=1;k<=N;k++){
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                if(distance[i][j]>distance[i][k]+distance[k][j])
                    distance[i][j]=distance[i][k]+distance[k][j];
            }
        }
    }

    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            
            if(distance[i][j]==101){
                MIN[i]=0;
                break;
            }
            else if(i==j)
                continue;
            else if(MIN[i]==0)
                MIN[i] = distance[i][j];
            else if(distance[i][j]>MIN[i])
                MIN[i]=distance[i][j];
        }        
    }

    // for(int i=0;i<=N;i++)
    //     printf("%d %d\n",i,MIN[i]);
    int flag = 1;
    int min[2] = {101,0};
    for(int i=1;i<=N;i++){
        if(MIN[i]&&MIN[i]<min[0]){
            flag = 0;
            min[0] = MIN[i];
            min[1] = i;
        }       
    }
        
    if(flag)
        printf("0");
    else{
        printf("%d %d",min[1],min[0]);
    }
    return 0;
}
