#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Member {         // typedef struct { int x; int y; } Point; allows you to declare a variable as Point myPoint; instead of the more complex struct { int x; int y; } myPoint;.

    int prn;
    char name[50];
    char position[20];
    struct Member* next;
} Member;

Member* head = NULL;

Member* createMember(int prn, char* name, char* position) {
    Member* newMember = (Member*)malloc(sizeof(Member));
   
    newMember->prn = prn;
    strcpy(newMember->name, name);
    strcpy(newMember->position, position);
    newMember->next = NULL;
   
    return newMember;
}

Member* addMember(int prn, char* name, char* position) {
    Member* newMember = createMember(prn, name, position);

    newMember->next = head;
    head = newMember;
   
    printf("Member %s (PRN: %d) added as %s successfully!\n", name, prn, position);
   
    return newMember;
}

void deleteMember(int prn) {
    if (head == NULL) {
        printf("Club is empty! No members to delete.\n");
        return;
    }
   
    Member* temp = head;
    Member* prev = NULL;
   
    //if deleting the head node
    if (temp != NULL && temp->prn == prn) {
        head = temp->next;
        printf("Member %s (PRN: %d, Position: %s) deleted successfully!\n",
               temp->name, temp->prn, temp->position);
        free(temp);
        return;
    }
   
    // Search for the member to be deleted
    while (temp != NULL && temp->prn != prn) {
        prev = temp;
        temp = temp->next;
    }
   
    // If member not found
    if (temp == NULL) {
        printf("Member with PRN %d not found!\n", prn);
        return;
    }
   
    // Unlink the node and free memory
    prev->next = temp->next;
    printf("Member %s (PRN: %d, Position: %s) deleted successfully!\n",
           temp->name, temp->prn, temp->position);
    free(temp);
}

void displaymembers(){
     if(head == NULL){
        printf("No members in the club.\n");
     }
     int count = 1;
     Member* temp = head;
     while(temp!=NULL){
        printf("Member %d name is %s (PRN: %d, Position: %s)\n", count, temp->name, temp->prn, temp->position);
        temp = temp->next;
        count++;
     }
     
     printf("Total members in the club is %d.\n", count - 1);
}

Member* reverse() {
    struct Member* prev = NULL;
    struct Member* current = head;
    struct Member* next;
   
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
   
    return prev;
}

Member* bubbleSort() {
    if (head == NULL) return head;
   
    int swapped;
    Member* ptr1;
    Member* lptr = NULL;  // Last sorted node
   
    do {
        swapped = 0;
        ptr1 = head;
       
        while (ptr1->next != lptr) {
       
            if (ptr1->next == NULL) break;
           
            if (ptr1->prn   >   ptr1->next->prn) {
                // Swap prn
                int temp = ptr1->prn;
                ptr1->prn = ptr1->next->prn;
                ptr1->next->prn = temp;
               
                 // Swap name
                char temp_name[50];
                strcpy(temp_name, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, temp_name);
               
                // Swap position
                char temp_position[20];
                strcpy(temp_position, ptr1->position);
                strcpy(ptr1->position, ptr1->next->position);
                strcpy(ptr1->next->position, temp_position);
               
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
   
    return head;
}

void displayaddress(){
    Member* temp = head;
    while(temp!=NULL){
       printf("%p \n", temp);
       temp = temp->next;
    }
}
int main(){
 
   int choice, prn;
   char name[50], position[20];
   
   while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Add Member\n");
        printf("2. Delete Member\n");
        printf("3. Display All Members\n");
        printf("4. Display the address of each Node\n");
        printf("5. Reverse the member list\n");
        printf("6. Sort the member list.\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
       
        scanf("%d", &choice);
       
        switch (choice) {
            case 1:
                printf("Enter PRN: ");
                scanf("%d", &prn);
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
               
                printf("Enter Position (Member/President/Secretary): ");
                scanf(" %[^\n]", position);
               
                addMember(prn, name, position);
                break;
               
            case 2:
                printf("Enter PRN of member to delete: ");
                scanf("%d", &prn);
                deleteMember(prn);
                break;
               
            case 3:
                displaymembers();
                break;
               
            case 4:
                displayaddress();
                break;
               
             case 5:
               head = reverse();
               break;
               
             case 6:
               head = bubbleSort();
               break;
               
         //   case 7:
         //       break;
                                                                                                                                                                                                                                                                                                                                                                                                                                                             
            case 7:
                exit(0);
                break;
           
            default:
                printf("Invalid choice.\n");
        }
    }
   
   
  return 0;

}