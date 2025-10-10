#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct student{
    int rollno;
    char name[10];
    float marks;
};

void accept(struct student s[10], int n)
{
    int ch;
    for(int i = 0; i < n; i++){
        printf("Enter roll no.\n");
        scanf("%d", &s[i].rollno);

        while((ch = getchar()) != '\n' && ch != EOF);

        printf("Enter name.\n");
        fgets(s[i].name, sizeof(s[i].name), stdin);

        printf("Enter marks.\n");
        scanf("%f", &s[i].marks);

        int ch;
        while((ch = getchar()) != '\n' && ch != EOF);
    }
}

void display(struct student s[10], int n){
    for(int i = 0; i < n; i++){
        printf("Name: %s\n", s[i].name);
        printf("Roll number: %d\n", s[i].rollno);
        printf("Marks obtained is: %.2f \n", s[i].marks);
        printf("---------------\n");
    }
}

void bubblesort(struct student s[10], int n){
    struct student temp;
    for(int i = n - 2; i >=0; i--){
        bool swapped = 0;
        for(int j = 0; j <= i; j++){
            if(s[j].marks > s[j+1].marks){
                temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) { break; }
    }
}

void insertionsort(struct student s[10], int n){
    struct student temp;
    for(int i = 1; i < n; i++){
        for(int j = i; j > 0; j--){
            if(s[j].rollno < s[j-1].rollno){
                temp = s[j];
                s[j] = s[j-1];
                s[j-1] = temp;
            }
            else {
                break;
            }
        }
    }
}

void selectionsort(struct student s[10], int n){
    struct student temp;
    int index, i;
    for(i = 0; i < n-1; i++){
        index = i;
        for(int j = i+1; j < n; j++){
            if(strcmp(s[j].name, s[index].name) < 0){
                index = j;
            }
        }
        temp = s[index];
        s[index] = s[i];
        s[i] = temp;
    }
}

int main(){
    struct student s[10];
    int n;
    printf("Enter the number of students.\n");
    scanf("%d", &n);

    accept(s, n);

    int c;
    printf("Press 1 to sort the student details by marks in ascending order using bubblesort.\n");
    printf("Press 2 to sort the student details by marks in ascending order using insertionsort.\n");
    printf("Press 3 to sort the student details by marks in ascending order using selectionsort.\n");
    scanf("%d", &c);

    switch(c){
        case 1:
            bubblesort(s, n);
            display(s, n);
            break;
        case 2:
            insertionsort(s, n);
            display(s, n);
            break;
        case 3:
            selectionsort(s, n);
            display(s, n);
            break;
        default : printf("invalid case\n");
    }

    return 0;
}