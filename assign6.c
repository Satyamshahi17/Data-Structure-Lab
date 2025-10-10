#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *left, *right;
};

struct node* stack[20];
int top = -1;
   
void push(struct node*ptr){
     top++;
     stack[top] = ptr;
}

struct node* pop(){
       struct node*temp = stack[top];
       top--;
       return temp;
}

struct node* peek() {
    return stack[top];
}

int isEmpty() {
       return (top == -1);
   }

void non_rec_create(struct node** root)
{
     int loop = 1;
     char ch;
     do{
        struct node* ptr = (struct node*)malloc(sizeof(struct node));
        int data;
        printf("Enter the node data\n");
        scanf("%d", &data);
        getchar(); // consume newline
        ptr->data = data;
        ptr->left = NULL;
        ptr->right = NULL;
       
        if(*root == NULL){
            *root = ptr;
        } else {
            struct node*temp = *root;
            int flag = 1;
            while(flag == 1){
                  printf("Where do you want to attach (l/r) of %d: ", temp->data);
                  scanf(" %c", &ch);
                  if(ch == 'l'){
                     if(temp->left == NULL){
                        temp->left = ptr;
                        flag = 0;                    
                     } else {
                      temp = temp->left;
                     }
                  } else {
                     if(temp->right == NULL){
                        temp->right = ptr;
                        flag = 0;                    
                     } else {
                      temp = temp->right;
                     }
                  }
            }
        }
        printf("\nContinue?? If yes, Press 1 else 0.\n");
        scanf("%d", &loop);
     }while(loop==1);
}

struct node* rec_create() {
    int data;
    char choice;

    printf("Enter data (or -1 for NULL): ");
    scanf("%d", &data);
    
    if (data == -1) return NULL;

    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    // Recursively create left child
    printf("Add left child for %d? (y/n): ", data);
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
        newNode->left = rec_create();  // Recursive call returns the child node

    // Recursively create right child
    printf("Add right child for %d? (y/n): ", data);
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
        newNode->right = rec_create();  // Recursive call returns the child node

    return newNode;  
}

void non_rec_inorder(struct node* root)
{
    struct node* temp = root;
    while(temp != NULL || top != -1){
          while(temp != NULL){        // Go to the leftmost node
                push(temp);
                temp = temp->left;
          }
          temp = pop();
          printf(" %d ", temp->data);
          temp = temp->right;          
    }
}

void non_rec_preorder(struct node* root)
{
    struct node* temp = root;
    while(temp != NULL || top != -1){
          while(temp != NULL){        // Go to the leftmost node
                printf(" %d ", temp->data);
                push(temp);
                temp = temp->left;
          }
          temp = pop();          
          temp = temp->right;          
    }
}

void non_rec_postorder(struct node* root) {
    if (root == NULL) return;
    
    struct node *temp= root;
    
    while (1) {
        // Go to leftmost node
        while (temp != NULL) {
            push(temp);
            temp = temp->left;
        }
        
        // Check if right child exists and hasn't been processed
        while (!isEmpty() && peek()->right == NULL) {
            temp = pop();
            printf("%d ", temp->data);  // Visit node
        }
        
        if (isEmpty())
            break;
        
        // Move to right subtree
        temp = peek()->right;
    }
    
}     //WRONG CAUSES INFINITE LOOP

void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf(" %d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct node* root)
{
    if (root != NULL) {
        printf(" %d ", root->data);
        preorder(root->left);      
        preorder(root->right);
    }
}

void postorder(struct node* root)
{
    if (root != NULL) {        
        postorder(root->left);      
        postorder(root->right);
        printf(" %d ", root->data);
    }
}

int main(){
   struct node* root = NULL;
//    non_rec_create(&root);
   
//    printf("\nInorder: ");
//    inorder(root);
//    printf("\nPreorder: ");
//    preorder(root);
//    printf("\nPostorder: ");
//    postorder(root);
   
   root = rec_create();
//    printf("\nInorder: ");
//    inorder(root);
//    printf("\nPreorder: ");
//    preorder(root);
//    printf("\nPostorder: ");
//    postorder(root);

    printf("\nNon Rec Inorder: ");
    non_rec_inorder(root);
    printf("\nNon Rec Preorder: ");
    non_rec_preorder(root);
    // printf("\nNon Rec Postorder: ");
    // non_rec_postorder(root);

   return 0;
}