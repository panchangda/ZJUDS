// #include <stdio.h>
// #include <math.h>
// #include <stdlib.h>

// typedef struct Node
// {
//     int data;
//     struct Node *left, *right;
// } * TreeNode;

// int a[1000];
// /*
//       1
//     2   3
//    4 5 6 7
//   8 9 0
//   6
// 3 8
// 1 5 7 9
// 0 2 4
// */
// //1 2 4 8 16
// TreeNode BuildTree(int height, int extra, int base)
// {
//     int extraL, extraR;
//     if (extra > pow(2, --height))
//     {
//         extraL = pow(2, height);
//         extraR = extra - pow(2, height);
//     }
//     else
//     {
//         extraL = extra;
//         extraR = 0;
//     }
//     int t = pow(2, height) + extraL - 1 + base;
//     TreeNode NewNode = (TreeNode)malloc(sizeof(struct Node));
//     NewNode->left = BuildTree(height, extraL, 0);
//     NewNode->right = BuildTree(height, extraR, t);
//     NewNode->data = a[t];

//     return NewNode;
// }

// void LevelTraversal()
// {
// }

// int main()
// {
//     int n, tmpLevelAmount, m = 1;
//     double idx = 0;
//     scanf("%lf", &n);
//     for (int i = 0; i < n; i++)
//     {
//         scanf("%d", &a[i]);
//     }

//     while (n - m > tmpLevelAmount)
//     {
//         m += pow(2, ++idx);
//         tmpLevelAmount = pow(2, idx);
//     }
//     BuildTree(idx, n - m, 0);
//     LevelTraversal();
// }

// void inorder(int k)
// {
//     if(k>n)return ;

// }

#include <stdio.h>
int n, a[1001], res[1001], idx = 0;
void inorder(int k)
{
    if (k > n)
        return;
    inorder(k * 2);
    res[k] = a[idx++];
    inorder(k * 2 + 1);
}
void leveltraversal()
{
    for (int i = 1; i <= n; i++)
    {
        if (i == 1)
            printf("%d", res[i]);

        else
            printf(" %d", res[i]);
    }
}
int main()
{   
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(int i =0;i<n;i++){
        for(int j=i;j<n;j++){
            if(a[j]<a[i]){
                int temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
    inorder(1);
    leveltraversal();
    return 0;
}