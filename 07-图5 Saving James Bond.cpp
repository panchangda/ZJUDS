#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
#include <stack>
using namespace std;

typedef struct crocodile
{
    int x, y;
} crocodile;

crocodile crocs[100];
int path[100];
int visited[100];
int Escaped = 0;
int N, D;

int NearCenterEnough(int x, int y)
{
    return (pow(x, 2) + pow(y, 2) <= pow(D + 7.5, 2) ? 1 : 0);
}
int CanJump(int x1, int y1, int x2, int y2)
{
    return (pow(x1 - x2, 2) + pow(y1 - y2, 2) <= pow(D, 2) ? 1 : 0);
}
int CanEscape(int x, int y)
{
    return (x - D <= -50 || x + D >= 50 || y - D <= -50 || y + D >= 50 ? 1 : 0);
}
//sb test point 😅😅😅
int OneJump()
{
    return (D >= 35 ? 1 : 0);
}
int OnIsland(int x, int y)
{
    return (pow(x, 2) + pow(y, 2) <= pow(7.5, 2) ? 1 : 0);
}
int OnShore(int x, int y)
{
    return (x >= 50 || x <= -50 || y >= 50 || y <= -50 ? 1 : 0);
}

int BFS(int start)
{
    queue<int> q;
    q.push(start);
    path[start] = -1;
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        visited[tmp] = 1;
        if (CanEscape(crocs[tmp].x, crocs[tmp].y))
        {
            Escaped = 1;
            return tmp;
            break;
        }

        for (int i = 0; i < N; i++)
        {
            if (!visited[i] && CanJump(crocs[tmp].x, crocs[tmp].y, crocs[i].x, crocs[i].y))
            {
                q.push(i);
                path[i] = tmp;
            }
        }
    }
    return -1;
}
int main()
{
    scanf("%d %d", &N, &D);

    //sb test point 😅😅😅
    if (OneJump())
    {
        printf("1");
        return 0;
    }
    for (int i = 0; i < N; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        crocs[i].x = x;
        crocs[i].y = y;
        if (OnShore(x, y) || OnIsland(x, y))
        {
            crocs[i].x = 50 + D;
            crocs[i].y = 50 + D;
        }
    }

    int EscapedPathEnd = -1;
    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && NearCenterEnough(crocs[i].x, crocs[i].y))
        {
            int tmp = BFS(i);
            if (tmp != -1)
            {
                if (EscapedPathEnd == -1)
                {
                    EscapedPathEnd = tmp;
                }
                else
                {
                    int start1 = tmp;
                    int start2 = EscapedPathEnd;
                    while (path[start1] != -1)
                        start1 = path[start1];
                    while (path[start2] != -1)
                        start2 = path[start2];
                    if (pow(crocs[start1].x, 2) + pow(crocs[start1].y, 2) < pow(crocs[start2].x, 2) + pow(crocs[start2].y, 2))
                        EscapedPathEnd = tmp;
                }
            }
        }
    }

    if (Escaped)
    {
        stack<int> s;
        int count = 2;
        while (path[EscapedPathEnd] != -1)
        {

            count++;
            s.push(EscapedPathEnd);
            EscapedPathEnd = path[EscapedPathEnd];
        }
        
        s.push(EscapedPathEnd);
        printf("%d\n", count);
        while (!s.empty())
        {
            int tmp = s.top();
            s.pop();
            printf("%d %d\n", crocs[tmp].x, crocs[tmp].y);
        }
    }
    else
        printf("0");

    return 0;
}