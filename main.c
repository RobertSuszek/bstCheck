#include <stdio.h>
#include <stdlib.h>

//structure for holding a single tree node
struct node {
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
};

//returns pointer to allocated node and fills it with value
struct node *createNode(int value);

//if none of childs is null, does nothing and returns 1, otherwise inserts node into tree and returns 0
int insertNode(struct node **root, struct node *node);

//adds node with specified value into tree (based on insertNode)
int addNode(struct node **root, int value);

//returns pointer to allocated node and fills it with value
struct node *createNode(int value) {
    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = value;
    return newNode;
}

//if none of childs is null, does nothing and returns 1, otherwise inserts node into tree and returns 0
int insertNode(struct node **root, struct node *node) {
    if ((*root)->left == NULL) {
        node->parent = (*root);
        (*root)->left = node;
        return 0;
    } else if ((*root)->right == NULL) {
        node->parent = (*root);
        (*root)->right = node;
        return 0;
    } else
        return 1;
}

int addNode(struct node **root, int value) {
    struct node *newNode = createNode(value);
    return 1;
}

int main()
{
    struct node *root;


    return 0;
}
