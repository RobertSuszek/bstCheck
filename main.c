#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure for holding a single tree node
struct node {
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
};

//returns pointer to allocated node and fills it with value
struct node *createNode(int value);

//adds node with specified value into tree (based on insertNode)
int addNode(struct node **root, int value);

//returns next line of file
char *getNextLine(FILE *file);

struct node *createNode(int value) {
    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = value;
    return newNode;
}
int addNode(struct node **root, int value) {
    struct node *newNode = createNode(value);
    (*root) = newNode;
}

void analyzeLine(struct node **root, FILE **file) {
    char line[256];
    int value;
    if (ferror((*file)) == 0) {
        fgets(line, 256, (*file));
        if (strchr(line, '/') == NULL) {
            strtok(line, "<node=");
            value = atoi(line);
            printf("Dodaje node %i\n", value);
            addNode(root, value);
            analyzeLine(&((*root)->left), file);
        }
    }
}

int readTreeFromFile(struct node **root, char *path) {
    FILE *file = fopen(path, "r");
    if (file != NULL) {

    } else
        return 1;
}

int main()
{
    struct node *root = NULL;

    return 0;
}
