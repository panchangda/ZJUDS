#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTNode
{
    int data;
    struct BSTNode *left, *right;
} * TreeNode;

int num = 0;
char Original[11], Other[11];

void insert(TreeNode node, TreeNode root)
{
    if (node->data < root->data)
    {
        if (root->left != NULL)
            insert(node, root->left);
        else
            root->left = node;
    }
    else if (node->data > root->data)
    {
        if (root->right != NULL)
            insert(node, root->right);
        else
            root->right = node;
    }
}

void Traversal(char *result, TreeNode root)
{   
    if (root)
    {
        result[num++] = root->data;
        Traversal(result, root->left);
        Traversal(result, root->right);
    }
}

int main()
{
    int length, n;
    while (scanf("%d", &length) != EOF && length != 0)
    {
        TreeNode root;
        scanf("%d", &n);
        for (int i = 0; i < length; i++)
        {
            int data;
            scanf("%d", &data);
            TreeNode NewNode = (TreeNode)malloc(sizeof(struct BSTNode));
            NewNode->data = data;
            NewNode->left = NULL;
            NewNode->right = NULL;
            if (i == 0)
                root = NewNode;
            else
                insert(NewNode, root);
        }
        num = 0;
        Traversal(Original, root);

        // for (int k = 0; k < length; k++)
        //     printf("%d ", Original[k]);

        for (int count = 0; count < n; count++)
        {
            for (int i = 0; i < length; i++)
            {
                int data;
                scanf("%d", &data);
                TreeNode NewNode = (TreeNode)malloc(sizeof(struct BSTNode));
                NewNode->data = data;
                NewNode->left = NULL;
                NewNode->right = NULL;
                if (i == 0)
                    root = NewNode;
                else
                    insert(NewNode, root);
            }

            num = 0;
            Traversal(Other, root);

            // for (int k = 0; k < length; k++)
            //     printf("%d ", Other[k]);

            if (strcmp(Original, Other) == 0)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}