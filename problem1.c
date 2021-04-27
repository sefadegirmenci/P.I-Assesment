#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//global variables
int sum_total = 0;
int max_all = 0;

//nodes of the tree
struct node
{
    struct node *left;
    struct node *right;
    int data;
    int height;
};
//tree structure
struct tree
{
    int height;
    struct node *root;
};

typedef struct node Node;
typedef Node *Node_ptr;
typedef struct tree Tree;

int prime(int);
int findHeight(int *, int); /*Find the height of the pramit*/
void inOrderTraversal(Node_ptr);
Tree *pyramid;

int main()
{
    printf("How many inputs?\n");
    int count;
    scanf("%d", &count);
    printf("Enter inputs\n");
    int *arr = malloc(sizeof(int) * count);
    Node_ptr *nodes = malloc(sizeof(Node_ptr) * count);

    for (int i = 0; i < count; i++)
    {
        scanf("%d", &arr[i]);
        nodes[i] = (Node_ptr)malloc(sizeof(Node));
    }

    /*Initialize nodes and the tree*/
    pyramid = malloc(sizeof(Tree));
    int offset = 1;
    int corner = offset;
    int current_height = 1;
    int height_total = findHeight(arr, count);
    for (int i = 0; i < count; i++)
    {
        if (i == corner)
        {
            current_height++;
            offset++;
            corner += offset;
        }
        nodes[i]->data = arr[i];
        nodes[i]->height = current_height;
        if (current_height != height_total)
        {
            nodes[i]->left = nodes[i + current_height];
            nodes[i]->right = nodes[i + current_height + 1];
        }
        else
        {
            nodes[i]->left = NULL;
            nodes[i]->right = NULL;
        }
    }
    pyramid->root = nodes[0];
    pyramid->height = height_total;

    /*Using inorder traversal logic, find maximum sum*/
    inOrderTraversal(pyramid->root);
    printf("Max sum = %d\n", max_all);

    /*Free allocated memory*/
    free(arr);
    free(pyramid);
    for (int i = 0; i < count; i++)
    {
        free(nodes[i]);
    }
}
/*Recursive in order traversal in the tree to find the path with maximum sum*/
void inOrderTraversal(Node_ptr root)
{
    if (root == NULL)
        return;
    sum_total += root->data;
    if (root->height == pyramid->height && max_all < sum_total)
    {
        max_all = sum_total;
    }
    if (root->left != NULL)
    {
        if (prime(root->left->data) == 1)
        {
            inOrderTraversal(root->left);
            sum_total -= root->left->data;
        }
    }
    if (root->right != NULL)
    {
        if (prime(root->right->data) == 1)
        {
            inOrderTraversal(root->right);
            sum_total -= root->right->data;
        }
    }
}

/*Prime number check*/
int prime(int val)
{
    for (int i = 2; i <= val / 2; i++)
    {
        if (val % i != 0)
            continue;
        else
            return 1;
    }
    if(val==1) return 1;
    return 0;
}

/*Find height of the pyramid*/
int findHeight(int *arr, int height)
{
    int current = 0;
    int current_level = 1;
    int left = current + current_level;
    while (left <= height)
    {
        current_level++;
        current = left;
        left = current + current_level;
    }
    return current_level - 1;
}
