#include <stdio.h>
#include <stdlib.h>
#define MAX 5

int arr[MAX];
int front_linear = -1;
int rear_linear = -1;

int is_empty(){
    return (front_linear > rear_linear || front_linear == -1);
}

int is_full(){
    return (rear_linear == MAX - 1);
}

int enqueue_linear(int data){
   if(is_full()){
         printf("Job Queue is full.\n");
         return 0;
       }
       
    if(front_linear == -1){
        front_linear = 0;
      }  
     
    rear_linear++;
    arr[rear_linear] = data;
    return 1;
}

int dequeue_linear(){
    if(is_empty()){
         printf("Job Queue is empty.\n");
         return 0;
       }
   
    front_linear++;
    return 1;
}

void displayLinear() {
    if (is_empty()) {
        printf("Job Queue is empty\n");
        return;
    }
   
    printf("Linear Job Queue: ");
    for (int i = front_linear; i <= rear_linear; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

#define N MAX
int Q[N];
int front = 0;
int rear = 0;

void AddCQ(int elem) {
    if ((rear + 1) % N == front) {
        printf("Circular Job Queue is full. Overwriting oldest element.\n");
        front = (front + 1) % N;
        rear = (rear + 1) % N;
        Q[rear] = elem;
    } else {
        rear = (rear + 1) % N;
        Q[rear] = elem;
    }
}

void DeleteCQ() {
    if (front == rear) {
        printf("Circular Job Queue is empty.\n");
    } else {
        front = (front + 1) % N;
    }
}

void DisplayCQ() {
    int i = (front + 1) % N;
    if (front == rear) {
        printf("Circular Job Queue is empty\n");
        return;
    }
    printf("Circular Job Queue: ");
    while (i != (rear + 1) % N) {
        printf("%d ", Q[i]);
        i = (i + 1) % N;
    }
    printf("\n");
}

int main(){
  front_linear = -1;
  rear_linear = -1;
  front = 0;
  rear = 0;

  printf(" Welcome to the Job Queue Management System!\n");
  printf("Press 1 for Linear Queue.\nPress 2 for Circular Queue.\n");
  int choice;
  scanf("%d", &choice);

  int c = 1;
  while(1){
          printf("MENU:\n");
          printf("Press 0 to exit.\n");
          printf("Press 1 to add job ID.\n");
          printf("Press 2 to delete job ID.\n");
          printf("Press 3 to view all jobs.\n");

          scanf("%d", &c);
          if(c==0){
             break;
          }

          switch(c){
                case 1:  {
                  int id;
                  printf("Enter the job ID you want to add.\n");
                      scanf("%d", &id);
                  if(choice == 1){
                      enqueue_linear(id);  
                  } else {
                      AddCQ(id);
                  }
                  break;          
                }

                case 2:  {
                  if(choice == 1){
                      dequeue_linear();
                  } else {
                      DeleteCQ();
                  }
                  break;
                }

                case 3:  {
                  if(choice == 1){
                      displayLinear();
                  } else {
                      DisplayCQ();
                  }
                  break;          
                }

                default: {
                   printf("Invalid choice!\n");
                }
          }
  }
  return 0;
}