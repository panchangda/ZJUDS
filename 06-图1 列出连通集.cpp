#include <stdio.h>
#include <queue>

int vertex[10][10];
int visited[10];
int N, E;

// 0 1 1 0 0 0 0 1
// 1 0 0 0 1 0 0 0
// 1 0 0 0 1 0 0 0
// 0 0 0 0 0 1 0 0
// 0 1 1 0 0 0 0 0
// 0 0 0 1 0 0 0 0
// 0 0 0 0 0 0 0 0
// 1 0 0 0 0 0 0 0

void DFS(int v)
{
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < N; i++)
    {
        if (vertex[v][i] && !visited[i])
        {
            DFS(i);
        }
    }
}
void BFS(int v)
{
    std::queue<int> q;
    q.push(v);
    visited[v] = 1;
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        printf("%d ", tmp);
        for (int i = 0; i < N; i++)
        {
            if (vertex[tmp][i] && !visited[i])
            {
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}
int main()
{
    scanf("%d %d", &N, &E);
    for (int i = 0; i < E; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        vertex[a][b] = 1;
        vertex[b][a] = 1;
    }
    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            printf("{ ");
            DFS(i);
            printf("}\n");
        }
    }

    for (int i = 0; i < N; i++)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            printf("{ ");
            BFS(i);
            printf("}\n");
        }
    }
}