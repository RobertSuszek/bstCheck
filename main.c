#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
};

struct node *createNode();
void insertNode(struct node **root, struct node *node);

struct node *createNode() {
    struct node *newNode = (struct node*) malloc(sizeof(node));
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = 0;
}

void insertNode(struct node **root, struct node *node) {
    struct node *newNode = createNode();
}

int main()
{
    struct node *root;


    return 0;
}
