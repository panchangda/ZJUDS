#include <cstdio>
#include <stack>
using namespace std;

int main()
{
    int max, length, number;
    scanf("%d%d%d", &max, &length, &number);

    for (int i = 0; i < number; i++)
    {
        stack<int>S;
        bool can = true;
        for (int k=1,j = 0; j < length; j++)
        {
            int temp;
            scanf("%d", &temp);
            if(temp>=k){
                for(;k<=temp;k++)
                    S.push(k);
                if(S.size()>max){
                    can = false;  
                }
                else
                    S.pop();
            }
            else{
                if(S.empty()||S.top()!=temp){
                    can=false;
                  
                }
                else
                    S.pop();
            }
        }

        puts(can?"YES":"NO");
    }
    return 0;
}


// int main()
// {
//     int m, n, k;

//     for (scanf("%d%d%d", &m, &n, &k); k; --k)
//     {
//         bool can = true;
//         stack<int> s;
//         for (int i = 1, j = 0; j < n; ++j)
//         {
//             int x;
//             scanf("%d", &x);
//             if (can)
//             {
//                 if (i > x)
//                 {
//                     if (s.empty() || (s.top() != x))
//                     {
//                         can = false;
//                     }
//                     else
//                     {
//                         s.pop();
//                     }
//                 }
//                 else
//                 {
//                     for (; (i <= x) && (i <= n) && (s.size() <= m); ++i)
//                     {
//                         s.push(i);
//                     }
//                     if ((!s.empty()) && (s.size() <= m) && (s.top() == x))
//                     {
//                         s.pop();
//                     }
//                     else
//                     {
//                         can = false;
//                     }
//                 }
//             }
//         }
//         puts(can ? "YES" : "NO");
//     }
//     return 0;
// }