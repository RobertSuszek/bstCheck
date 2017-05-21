#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*+-----------------------------+
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
/*+-----------------------------+
  |      Type declarations      |
  +-----------------------------+*/

/* ---------------------------------------------------------------------------------------*/

/*+-----------------------------+
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
/*returns pointer to root of tree specified in file of given path if succeed, if not, returns NULL*/
struct node *parseFileToTree(char *path);
/*returns minimum value of given tree*/
int bstMin(struct node *node);
/*returns maximum value of given tree*/
int bstMax(struct node *node);
/*checks if given tree is BST*/
bool isBST(struct node *node);
/*deletes a single node of tree*/
int deleteNode(struct node *node);
/*deletes nodes in tree, which value is 0*/
void deleteEmptyNodes(struct node *node);
/*returns path to file given in params, otherwise returns NULL*/
char *getPathFromParam(int argc, char **argv);
/*prints information on standard output if given tree is BST or not*/
void printResult(bool isBST);
/*prints program help on standard output*/
void printHelp();
/*+-----------------------------+
  |    Function declarations    |
  +-----------------------------+*/

/* ---------------------------------------------------------------------------------------*/

/*+-----------------------------+
  |   Function implementations  |
  +-----------------------------+*/
struct node *createNode(int value) {
  struct node *newNode = (struct node*) malloc(sizeof(struct node));
  if (newNode) {
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = value;
  }
  return newNode;
}
int addChild(struct node **root, struct node *node) {
  if (root) {
    if (node) {
      if ((*root)->left == NULL) {
        node->parent = (*root);
        (*root)->left = node;
        return 0;
      } else if ((*root)->right == NULL) {
        node->parent = (*root);
        (*root)->right = node;
        return 0;
      } else
        return 3;
    } else
      return 2;
  } else
    return 1;
}
bool isStart(char *line) {
  if (line) {
    if (strchr(line, '='))
      return true;
    else
      return false;
  } else
    return false;
}
bool isEnd(char *line) {
  if (line) {
    if (strchr(line, '/'))
      return true;
    else
      return false;
  } else
    return false;
}
struct node *parseFileToTree(char *path) {
  FILE *file = fopen(path, "r");
  struct node *root = createNode(-1);
  struct node *current = root;
  int value;
  char line[256];
  if (file) {
    while (fgets(line, 256, file) != NULL) {
      if (isStart(line) == true) {
        if (sscanf(line, "%*[^0123456789]%i", &value));
        struct node *node = createNode(value);
        if (!node)
          return NULL;
        if ((addChild(&current, node)) != 0)
          return NULL;
        current = node;
      }
      if (isEnd(line) == true) {
        current = current->parent;
      }
      if ((isStart(line) == false) && (isEnd(line) == false)) {
        printf("Niepoprawna struktura pliku %s\n", path);
        return NULL;
      }
    }
    fclose(file);
    root = root->left;
    deleteEmptyNodes(root);
    deleteNode(root->parent);
    root->parent = NULL;
    return root;
  } else {
      printf("Nie udalo sie otworzyc pliku %s\n", path);
      return NULL;
    }
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
  if ((!(isBST(node->left))) || (!(isBST(node->right))))
    return false;
  return true;
}
int deleteNode(struct node *node) {
  if (node) {
    if (node->parent) {
      if (node->parent->left == node)
        node->parent->left = NULL;
      else
        node->parent->right = NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->value = 0;
    node->parent = NULL;
    free(node);
    return 0;
  } else
    return 1;
}
void deleteEmptyNodes(struct node *node) {
  if(node) {
    if ((node->left) && (node->left->value == 0) &&
        (node->left->left == NULL) && (node->left->right == NULL) &&
        (node->right) && (node->right->value != 0))
      deleteNode(node->left);
    deleteEmptyNodes(node->left);
    deleteEmptyNodes(node->right);
  }
}
char *getPathFromParam(int argc, char **argv) {
  int i;
  if (argc > 1) {
    for (i = 1; i < argc; i++) {
      if (!(strcmp(argv[i], "-h"))) {
        printHelp();
        return NULL;
      }
      if ((!(strcmp(argv[i], "-i"))) && (argc > i))
        return argv[i+1];
    }
    return NULL;
  } else
    return NULL;
}
void printResult(bool isBST) {
  if (isBST == true)
    printf("Drzewo JEST drzewem poszukiwan binarnych.");
  else
    printf("Dzrewo NIE JEST drzewem poszukiwan binarnych.");
}
void printHelp() {
  printf("Program SprawdzenieDrzewa sluzy do sprawdzenia, czy dane drzewo jest drzewem poszukiwan binarnych (BST)."
       "\n"
       "\nParametry wywolania programu:"
       "\n -i \"sciezka\""
       "\n"
       "\nDrzewo powinno byc w pliku opartym o format XML, do programu dolaczono przyklad poprawnego pliku z drzewem."
       "\nGdy zajdzie potrzeba, aby wezel posiadal prawego, lecz nie posiadal lewego syna, nalezy w miejsce lewego syna umiescic wezel o wartosci '0'.");
}
/*+-----------------------------+
  |   Function implementations  |
  +-----------------------------+*/

/* ---------------------------------------------------------------------------------------*/

int _print_t(struct node *tree, int is_left, int offset, int depth, char s[20][255]) {
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->value);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    int i = 0;
    for (i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_t(struct node *tree) {
    char s[20][255];
    int i = 0;
    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

int main(int argc, char **argv) {
  struct node *root = NULL;
  char *path = getPathFromParam(argc, argv);
  if (path) {
    root = parseFileToTree(path);
    if (!(root)) {
      printf("Wystapil problem z odczytaniem drzewa z pliku %s\n", path);
      printHelp();
      return 0;
    }
    printResult(isBST(root));
  } else {
    printf("Wystapil problem z odczytaniem œcie¿ki pliku z parametru\n");
    printHelp();
    return 0;
  }
  return 0;
}
