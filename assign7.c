#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char word[10];
    char meaning[20];
    struct node* left;
    struct node* right;
};

// Queue for level-wise display
struct node *Q[20];
int f = -1;
int r = -1;

void qinsert(struct node *t){
    r++;
    Q[r] = t;
}

struct node *qdelete(){
    f++;
    struct node* t = Q[f];
    return t;
}

int qempty() {
    if(f == r){
        return 1;
    }
    else {
        return 0;
    }
}

// CREATE FUNCTION: Insert nodes into BST
void create(struct node* root){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    char choice = 'y';
    do {
        temp = root;
        int flag = 0;
        struct node* curr = (struct node*)malloc(sizeof(struct node));
        
        printf("Enter the word: ");
        scanf("%s", curr->word);
        
        printf("Enter the meaning: ");
        scanf("%s", curr->meaning);
        
        curr->left = NULL;
        curr->right = NULL;
        
        while(flag == 0){
            if(strcmp(curr->word, temp->word) < 0) {
                if(temp->left == NULL) {
                    temp->left = curr;
                    flag = 1;
                }
                else {
                    temp = temp->left;
                }
            }
            else {
                if(temp->right == NULL) {
                    temp->right = curr;
                    flag = 1;
                }
                else {
                    temp = temp->right;
                }
            }
        }
        
        printf("Do you want to add another node? (y/n): ");
        scanf(" %c", &choice);
    } while(choice == 'y');
}

// DELETE FUNCTION: Delete a word from BST
struct node* deleteNode(struct node* root, char word[]) {
    if(root == NULL) {
        return root;
    }
    
    // Search for the node to delete
    if(strcmp(word, root->word) < 0) {
        root->left = deleteNode(root->left, word);
    }
    else if(strcmp(word, root->word) > 0) {
        root->right = deleteNode(root->right, word);
    }
    else {
        // Node found - handle three cases
        
        // Case 1: Leaf node (both left and right are NULL)
        if(root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // Case 2: Node with only right child (left is NULL)
        else if(root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        
        // Case 3: Node with only left child (right is NULL)
        else if(root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 4: Node with both children
        else {
            // Find inorder successor (leftmost in right subtree)
            struct node* s = root->right;
            struct node* temp = root->left;
            
            // Traverse to leftmost node in right subtree
            while(s->left != NULL) {
                s = s->left;
            }
            
            // Connect left subtree to inorder successor
            s->left = temp;
            
            // Store right child and free current node
            temp = root->right;
            free(root);
            
            return temp;
        }
    }
    
    return root;
}

// MIRROR IMAGE FUNCTION: Create mirror of binary tree
// Swaps left and right children recursively
void mirrorImage(struct node* root) {
    if(root == NULL) {
        return;
    }
    
    // Swap left and right children
    struct node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // Recursively mirror left and right subtrees
    mirrorImage(root->left);
    mirrorImage(root->right);
}

// DISPLAY LEVEL WISE: Display tree nodes level by level using queue
void displayLevelWise(struct node* root) {
    if(root == NULL) {
        printf("Tree is empty!\n");
        return;
    }
    
    // Reset queue pointers
    f = -1;
    r = -1;
    
    printf("\nLevel-wise Display:\n");
    
    qinsert(root);
    qinsert(NULL); // Level separator
    
    int level = 0;
    printf("Level %d: ", level);
    
    while(!qempty()) {
        struct node* temp = qdelete();
        
        if(temp == NULL) {
            // End of current level
            printf("\n");
            if(!qempty()) {
                level++;
                printf("Level %d: ", level);
                qinsert(NULL); // Add separator for next level
            }
        }
        else {
            printf("%s ", temp->word);
            
            if(temp->left != NULL) {
                qinsert(temp->left);
            }
            if(temp->right != NULL) {
                qinsert(temp->right);
            }
        }
    }
}

// COPY FUNCTION (Recursive): Create exact copy of BST
// Following the logic from slide 89
struct node* copyRecursive(struct node* root) {
    struct node* temp = NULL;
    
    if(root == NULL) {
        return NULL;
    }
    
    // Allocate memory for new node
    temp = (struct node*)malloc(sizeof(struct node));
    strcpy(temp->word, root->word);
    strcpy(temp->meaning, root->meaning);
    
    // Recursively copy left and right subtrees
    temp->left = copyRecursive(root->left);
    temp->right = copyRecursive(root->right);
    
    return temp;
}

// COPY FUNCTION (Non-Recursive): Create copy using stack approach
// Following the logic from slide 90
struct node* copyNonRecursive(struct node* root2) {
    if(root2 == NULL) {
        return NULL;
    }
    
    // Stack for traversal
    struct node* stack1[50];
    struct node* stack2[50];
    int top = -1;
    
    // Allocate memory for root1 (copy root)
    struct node* root1 = (struct node*)malloc(sizeof(struct node));
    struct node* temp1 = root1;
    struct node* temp2 = root2;
    
    // Copy root data
    strcpy(temp1->word, temp2->word);
    strcpy(temp1->meaning, temp2->meaning);
    temp1->left = NULL;
    temp1->right = NULL;
    
    while(1) {
        // Process left subtree
        while(temp2 != NULL) {
            if(temp2->left != NULL) {
                // Allocate memory for temp1->left
                temp1->left = (struct node*)malloc(sizeof(struct node));
                strcpy(temp1->left->word, temp2->left->word);
                strcpy(temp1->left->meaning, temp2->left->meaning);
                temp1->left->left = NULL;
                temp1->left->right = NULL;
            }
            
            if(temp2->right != NULL) {
                // Allocate memory for temp1->right
                temp1->right = (struct node*)malloc(sizeof(struct node));
                strcpy(temp1->right->word, temp2->right->word);
                strcpy(temp1->right->meaning, temp2->right->meaning);
                temp1->right->left = NULL;
                temp1->right->right = NULL;
            }
            
            // Push both nodes to stack
            top++;
            stack1[top] = temp1;
            stack2[top] = temp2;
            
            // Move to left child
            temp1 = temp1->left;
            temp2 = temp2->left;
        }
        
        if(top == -1) {
            break;
        }
        else {
            // Pop from stack
            temp1 = stack1[top];
            temp2 = stack2[top];
            top--;
            
            // Move to right child
            temp1 = temp1->right;
            temp2 = temp2->right;
        }
    }
    
    return root1;
}

// INORDER DISPLAY: Display tree in sorted order
void inorder(struct node* root) {
    if(root != NULL) {
        inorder(root->left);
        printf("%s: %s\n", root->word, root->meaning);
        inorder(root->right);
    }
}

int main() {
    struct node* root = (struct node*)malloc(sizeof(struct node));
    struct node* copiedTree = NULL;
    int choice;
    char wordToDelete[10];
    
    // Create root node
    printf("Enter root word: ");
    scanf("%s", root->word);
    printf("Enter root meaning: ");
    scanf("%s", root->meaning);
    root->left = NULL;
    root->right = NULL;
    
    do {
        printf("\n--- MENU ---\n");
        printf("1. Add words to dictionary\n");
        printf("2. Display dictionary (Inorder)\n");
        printf("3. Display level-wise\n");
        printf("4. Delete a word\n");
        printf("5. Create mirror image\n");
        printf("6. Copy tree (Recursive)\n");
        printf("7. Copy tree (Non-Recursive)\n");
        printf("8. Display copied tree\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                create(root);
                break;
            
            case 2:
                printf("\nDictionary Contents (Inorder):\n");
                printf("------------------------------\n");
                inorder(root);
                break;
            
            case 3:
                displayLevelWise(root);
                break;
            
            case 4:
                printf("Enter word to delete: ");
                scanf("%s", wordToDelete);
                root = deleteNode(root, wordToDelete);
                printf("Word deleted (if found).\n");
                break;
            
            case 5:
                mirrorImage(root);
                printf("Mirror image created!\n");
                printf("Display tree to see the result.\n");
                break;
            
            case 6:
                copiedTree = copyRecursive(root);
                printf("Tree copied using recursive method!\n");
                break;
            
            case 7:
                copiedTree = copyNonRecursive(root);
                printf("Tree copied using non-recursive method!\n");
                break;
            
            case 8:
                if(copiedTree != NULL) {
                    printf("\nCopied Tree Contents:\n");
                    printf("--------------------\n");
                    inorder(copiedTree);
                }
                else {
                    printf("No copied tree exists. Create a copy first.\n");
                }
                break;
            
            case 9:
                printf("Exiting program.\n");
                break;
            
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 9);
    
    return 0;
}
