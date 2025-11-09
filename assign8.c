#include <stdio.h>
#include <stdlib.h>
/*  
While we don't follow any traversal during creation, the threads we set up are based on INORDER relationships!
Left thread → Points to inorder predecessor
Right thread → Points to inorder successor
*/
// Structure for threaded binary tree node
struct tbtnode {
    char data;
    int rbit, lbit;
    struct tbtnode *rightc;
    struct tbtnode *leftc;
};

typedef struct tbtnode tbtnode;

// Function to create the threaded binary tree
void create(tbtnode *head) {
    int flag = 0;
    tbtnode *root, *temp, *curr;
    char ch;
    
    // Allocate memory for root and accept root data
    root = (tbtnode *)malloc(sizeof(tbtnode));
    printf("Enter root data: ");
    scanf(" %c", &root->data);
    
    // Assign head lbit to 1
    head->lbit = 1;
    
    // Assign root->leftc and rightc to head
    root->leftc = head;    // Points to HEAD (not a child!)
    root->rightc = head;   // Points to HEAD (not a child!)
    
    // Assign root->lbit and rbit to 0
    root->rbit = 0;    // Tell everyone: "rightc is a THREAD!"
    root->lbit = 0;    // Tell everyone: "leftc is a THREAD!"
    
    // Assign head->leftc to root
    head->leftc = root;
    
    do {
        // Initialize flag to 0
        flag = 0;
        temp = root;
        
        // Allocate memory to curr and accept curr->data
        curr = (tbtnode *)malloc(sizeof(tbtnode));
        printf("Enter data: ");
        scanf(" %c", &curr->data);
        
        // Assign curr->lbit and rbit to 0
        curr->lbit = 0;
        curr->rbit = 0;
        
        while(flag == 0) {
            // Accept choice left or right
            printf("Accept choice left or right (l/r): ");
            scanf(" %c", &ch);
            
            if(ch == 'l') {
                if(temp->lbit == 0) {
                    curr->leftc = temp->leftc;
                    curr->rightc = temp;
                    temp->leftc = curr;
                    temp->lbit = 1;
                    flag = 1;
                }
                else {
                    temp = temp->leftc;
                }
            }
            else if(ch == 'r') {
                if(temp->rbit == 0) {
                    curr->leftc = temp;
                    curr->rightc = temp->rightc;
                    temp->rightc = curr;
                    temp->rbit = 1;
                    flag = 1;
                }
                else {
                    temp = temp->rightc;
                }
            }
        }
        
        // Accept choice for continue
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &ch);
        
    } while(ch == 'y');
}

// Function to find inorder successor
tbtnode *inordersucc(tbtnode *temp) {
    tbtnode *x;
    x = temp->rightc;
    
    if(temp->rbit == 1) {
        while(x->lbit == 1)
            x = x->leftc;
    }
    
    return x;
}

// Function to perform inorder traversal
void inorder(tbtnode *head) {
    tbtnode *temp;
    
    // Assign temp to head->left
    temp = head->leftc;
    
    while(temp != head) {
        // Print temp->data
        printf("%c ", temp->data);
        
        // While temp->lbit != 0, move temp to temp->left and print temp->data
        while(temp->lbit != 0) {
            temp = temp->leftc;
            printf("%c ", temp->data);
        }
        
        // While temp->rbit == 0, move temp to temp->right
        while(temp->rbit == 0) {
            temp = temp->rightc;
            
            // If temp == head, break
            if(temp == head)
                break;
                
            printf("%c ", temp->data);
        }
        
        // Move temp to temp->right
        temp = temp->rightc;
    }
}

// Function to perform preorder traversal
void preorder(tbtnode *head) {
    tbtnode *temp;
    
    // Assign temp to head->left
    temp = head->leftc;
    
    while(temp != head) {
        // Print temp->data
        printf("%c ", temp->data);
        
        // While temp->lbit != 0, move temp to temp->left and print temp->data
        while(temp->lbit != 0) {
            temp = temp->leftc;
            printf("%c ", temp->data);
        }
        
        // While temp->rbit == 0, move temp to temp->right
        while(temp->rbit == 0) {
            temp = temp->rightc;
            
            // If temp == head, break
            if(temp == head)
                break;
        }
        
        // Move temp to temp->right
        temp = temp->rightc;
    }
}

int main() {
    tbtnode *head;
    
    // Allocate memory for head
    head = (tbtnode *)malloc(sizeof(tbtnode));
    
    // Initialize rbit to 1
    head->rbit = 1;
    head->lbit = 0;
    
    // head->left = head->right = head
    head->leftc = head;
    head->rightc = head;
    
    // Create threaded binary tree
    create(head);
    
    printf("\nInorder Traversal: ");
    inorder(head);
    
    printf("\n\nPreorder Traversal: ");
    preorder(head);
    
    printf("\n");
    
    return 0;
}
