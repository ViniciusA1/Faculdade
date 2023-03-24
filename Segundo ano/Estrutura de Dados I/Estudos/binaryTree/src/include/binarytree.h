#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1000

/* Tree format:
 *  value = integer element;
 * *left = points to the left side of node,
 * *right = points to the right side of node.
 */

typedef struct binary_tree {
        int value;
        struct binary_tree *left;
        struct binary_tree *right;
} binTree_t;

// Print Buffer.
typedef struct PrintString {
        char prev[BUFFERSIZE];
} print_t;


// ====|Prototypes|==== //

binTree_t *addElem(binTree_t *, int);
binTree_t *createElem(int);
binTree_t *rmElem(binTree_t *, int);
binTree_t *mostLeft(binTree_t *);
binTree_t *searchElem(binTree_t *, int);
void showTree(binTree_t *, print_t, char *, int);
void clearMemory(binTree_t *);
