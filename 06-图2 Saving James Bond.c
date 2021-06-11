#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct crocodile
{
    int x, y;
}crocodile;

crocodile crocs[100];

int visited[100];
int Escaped = 0;
int N, D;
int NearCenterEnough(int x, int y)
{
    return (pow(x, 2) + pow(y, 2) <= pow(D + 7.5, 2) ? 1 : 0);
}
int CanJump(int x1,int y1,int x2,int y2)
{
    return (pow(x1 - x2, 2) + pow(y1 - y2, 2) <= pow(D, 2) ? 1 : 0);
}
int CanEscape(int x, int y)
{
    return(x-D<=-50||x+D>=50||y-D<=-50||y+D>=50?1:0);
}
void DFS(int tmpCroc)
{
    if (CanEscape(crocs[tmpCroc].x,crocs[tmpCroc].y)){
        Escaped = 1;
        return;
    }
        

    visited[tmpCroc] = 1;
    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && CanJump(crocs[tmpCroc].x,crocs[tmpCroc].y,crocs[i].x,crocs[i].y))
        {
            DFS(i);
        }
    }
}

int main()
{
    scanf("%d %d", &N, &D);
    for (int i = 0; i < N; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        crocs[i].x = x;
        crocs[i].y = y;
    }
    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && NearCenterEnough(crocs[i].x, crocs[i].y))
        {
            DFS(i);
        }
    }

    if (Escaped)
        printf("Yes");
    else
        printf("No");

    return 0;
}