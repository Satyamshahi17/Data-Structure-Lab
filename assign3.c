#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

int stack[MAXSIZE];
int top = -1;

int isFull() {
    if (top == MAXSIZE - 1)
        return 1;
    else
        return 0;
}

int isEmpty() {
    if (top == -1)
        return 1;
    else
        return 0;
}

void push(int item) {
    if (!isFull()) {
        top = top + 1;
        stack[top] = item;
    } else {
        printf("Stack Overflow!\n");
    }
}

int pop() {
    if (!isEmpty()) {
        int temp = stack[top];
        top = top - 1;
        return temp;
    } else {
        printf("Stack Underflow!\n");
        return -1;
    }
}

int peek() {
    if (!isEmpty()) {
        return stack[top];
    } else {
        printf("Stack is empty!\n");
        return -1;
    }
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

void infix_to_postfix(const char* infix, char* postfix) {
    top = -1;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token >= '0' && token <= '9')) {
            postfix[j++] = token;
        }
        else if (token == '(') {
            push(token);
        }
        else if (token == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = peek();
                pop();
            }
            pop();
        }
        else {
            while (!isEmpty() && precedence(peek()) >= precedence(token)) {
                postfix[j++] = peek();
                pop();
            }
            push(token);
        }
    }

    while (!isEmpty()) {
        postfix[j++] = peek();
        pop();
    }

    postfix[j] = '\0';
}

void infix_to_prefix(const char* infix, char* prefix) {
    top = -1;
    int j = 0;

    // Reverse the infix expression
    int len = strlen(infix);
    char* rev_infix = (char*)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        rev_infix[i] = infix[len - 1 - i];
    }
    rev_infix[len] = '\0';

    for (int i = 0; rev_infix[i] != '\0'; i++) {
        char token = rev_infix[i];

        if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token >= '0' && token <= '9')) {
            prefix[j++] = token;
        }
        else if (token == ')') {
            push(token);
        }
        else if (token == '(') {
            while (!isEmpty() && peek() != ')') {
                prefix[j++] = peek();
                pop();
            }
            pop();
        }
        else {
            while (!isEmpty() && precedence(peek()) > precedence(token)) {
                prefix[j++] = peek();
                pop();
            }
            push(token);
        }
    }

    while (!isEmpty()) {
        prefix[j++] = peek();
        pop();
    }

    prefix[j] = '\0';

    // Reverse the prefix expression to get the final result
    for (int i = 0; i < j / 2; i++) {
        char temp = prefix[i];
        prefix[i] = prefix[j - 1 - i];
        prefix[j - 1 - i] = temp;
    }

    free(rev_infix);
}

int main() {
    char infix[MAXSIZE];
    char postfix[MAXSIZE];
    char prefix[MAXSIZE];

    // printf("Enter infix expression: ");
    // scanf("%s", infix);

    infix[0] = 'A';
    infix[1] = '+';
    infix[2] = 'B';
    infix[3] = '*';
    infix[4] = 'C';
    infix[5] = '-';
    infix[6] = 'D';
    infix[7] = '\0';

    printf("Infix expression: %s\n", infix);

    // Convert to postfix
    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    // Convert to prefix
    infix_to_prefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    return 0;
}