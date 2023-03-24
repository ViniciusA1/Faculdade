#include "include/binarytree.h"

// Adds the desired element to the binary tree.
binTree_t *addElem(binTree_t *aux, int wish)
{
        if(!aux)
                return createElem(wish);

        if(wish > aux->value)
                aux->right = addElem(aux->right, wish);
        else if(wish < aux->value)
                aux->left = addElem(aux->left, wish);

        return aux;
}

// Creates the data structure of the element.
binTree_t *createElem(int value)
{
        binTree_t *new = malloc(sizeof(binTree_t));
        new->value = value;
        new->left = new->right = NULL;

        return new;
}

// Removes an element from the tree.
binTree_t *rmElem(binTree_t *tmp, int target)
{
        if(!tmp)
                return tmp;

        if(target > tmp->value)
                tmp->right = rmElem(tmp->right, target);
        
        else if(target < tmp->value)
                tmp->left = rmElem(tmp->left, target);

        else {
                binTree_t *aux;

                if(!tmp->left || !tmp->right) {
                        aux = tmp->left ? tmp->left : tmp->right;
                        free(tmp);
                        return aux;
                }

                aux = mostLeft(tmp->right);
                tmp->value = aux->value;
                tmp->right = rmElem(tmp->right, tmp->value);
        }

        return tmp;
}

// Find the lowest value child.
binTree_t *mostLeft(binTree_t *begin)
{
        while(begin->left)
                begin = begin->left;

        return begin;
}

// Search for an element on the binary tree.
binTree_t *searchElem(binTree_t *aux, int target)
{
        if(!aux || aux->value == target)
                return aux;

        if(target > aux->value)
                return searchElem(aux->right, target);
                
        return searchElem(aux->left, target);
}

// Displays the whole tree (still need improvements).
void showTree(binTree_t *node, print_t prefix, char *variable_str, int isLeft)
{
        strcat(prefix.prev, variable_str);

        if(!node)
                return;

        if(node->right)
                showTree(node->right, prefix, (isLeft ? "│   " : "    "), 0);

        printf("%s%s%d\n", prefix.prev, isLeft ? "└── " : "┌── ", node->value);

        if(node->left)
                showTree(node->left, prefix, (isLeft ? "    " : "│   "), 1);
}

// Clear the allocated memory.
void clearMemory(binTree_t *tmp)
{
        if(!tmp)
                return;

        clearMemory(tmp->right);
        clearMemory(tmp->left);
        free(tmp);
}
