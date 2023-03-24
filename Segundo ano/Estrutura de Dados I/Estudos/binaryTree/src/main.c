// Binary Search Tree (BST).
// Example of operations.

// Binary tree header.
#include "include/binarytree.h"

// Local prototypes.
void startMenu(binTree_t *);
binTree_t *startMenuOptions(int, binTree_t *);
int getValue();
void pressEnter();

// Main function.
int main()
{
        // creates the root element.
        binTree_t *root = NULL;

        // go to start function.
        startMenu(root);
        return 0;
}

// Display start menu informations.
void startMenu(binTree_t *begin)
{
        int user_opt;

        do {
                fputs("\e[1;1H\e[2J", stdout);
                puts("====|Menu|====");
                puts("0) Close\n"
                     "1) Add element\n"
                     "2) Remove element\n"
                     "3) Search element\n"
                     "4) Show elements");
                fputs("> ", stdout);
                scanf("%d", &user_opt);

                begin = startMenuOptions(user_opt, begin);
        } while(user_opt);

        clearMemory(begin);
}

// Verify the option chosen by current user.
binTree_t *startMenuOptions(int chosen, binTree_t *start)
{
        print_t aux_str;
        aux_str.prev[0] = '\0';

        switch(chosen) {
                // leave
                case 0: 
                        return start;
                // add element
                case 1:
                        start = addElem(start, getValue());
                        puts("Element added!");
                        break;
                // remove element.
                case 2: 
                        start = rmElem(start, getValue());
                        puts("Element removed!");
                        break;
                // search for element.
                case 3: 
                        if(searchElem(start, getValue()))
                                puts("This number exists in the tree");
                        else
                                puts("This number doesn't exist in the tree");
                        break;
                // display everything.
                case 4:
                        puts("Current elements of the tree:");
                        showTree(start, aux_str, "", 0);
                        break;
                default: 
                        puts("Error! Invalid option!");
        }

        pressEnter();

        // returns the modified root.
        return start;
}

// Get the user input.
int getValue()
{
        int num;

        fputs("Enter a number: ", stdout);
        scanf("%d", &num);

        return num;
}

// "Pause".
void pressEnter()
{
        fputs("Press enter to continue...", stdout);
        scanf("%*c");
        getchar();
}
