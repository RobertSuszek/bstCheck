#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  +-----------------------------+
    |      Type declarations      |
    +-----------------------------+*/

/*typedef for bool in C*/
typedef enum { false, true } bool;

/*structure for holding a single tree node*/
struct node {
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
};

/*  +-----------------------------+
    |      Type declarations      |
    +-----------------------------+*/

/*  +-----------------------------+
    |    Function declarations    |
    +-----------------------------+*/

/*returns pointer to allocated node with value*/
struct node *createNode(int value);
/*inserts given node into left child, if not left child is free then inserts into right,
if not, does nothing and returns 1*/
int addChild(struct node **root, struct node *node);
/*checks if in the given line some node starts*/
bool isStart(char *line);
/*checks if in the given line some node ends*/
bool isEnd(char *line);
/*returns pointer to root of tree specified in file of given path*/
struct node *parseFileToTree(char *path);
/*returns minimum value of given tree*/
int bstMin(struct node *node);
/*returns maximum value of given tree*/
int bstMax(struct node *node);
/*checks if given tree is BST*/
bool isBST(struct node *node);

/*  +-----------------------------+
    |    Function declarations    |
    +-----------------------------+*/

/*  +-----------------------------+
    |   Function implementations  |
    +-----------------------------+*/
struct node *createNode(int value) {
    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = value;
    return newNode;
}
int addChild(struct node **root, struct node *node) {
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
bool isStart(char *line) {
    if (strchr(line, '='))
        return true;
    else
        return false;
}
bool isEnd(char *line) {
    if (strchr(line, '/'))
        return true;
    else
        return false;
}
struct node *parseFileToTree(char *path) {
    FILE *file = fopen(path, "r");
    struct node *root = createNode(-1);
    struct node *current = root;
    int value;
    char line[256];

    while (fgets(line, 256, file) != NULL) {
        if (isStart(line) == true) {
            sscanf(line, "%*[^0123456789]%i", &value);
            struct node *node = createNode(value);
            addChild(&current, node);
            current = node;
        }
        if (isEnd(line) == true) {
            current = current->parent;
        }
    }
    fclose(file);
    return root->left;
}
int bstMin(struct node *node) {
    if (node == NULL)
        return 0;

    while (node->left != NULL)
        node = node->left;

    return node->value;
}
int bstMax(struct node *node) {
    if (node == NULL)
        return 0;

    while (node->right != NULL)
        node = node->right;

    return node->value;
}
bool isBST(struct node *node) {
  if (node == NULL)
    return true;

  if ((node->left != NULL) && bstMax(node->left) > node->value)
    return false;

  if ((node->right != NULL) && bstMin(node->right) < node->value)
    return false;

  if ( (!(isBST(node->left))) || (!(isBST(node->right))) )
    return false;

  return true;
}
/*  +-----------------------------+
    |   Function implementations  |
    +-----------------------------+*/

int main()
{
    struct node *root = NULL;

    return 0;
}
