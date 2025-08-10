#include <stdio.h>
#include <string.h>

#define MAX 5
#define STR_LEN 50

// Queue for Pending Tasks
char pending[MAX][STR_LEN];
int front = -1, rear = -1;

// Stack for Completed Tasks
char completed[MAX][STR_LEN];
int top = -1;

// Enqueue function
void addTask(char task[]) {
    if (rear == MAX - 1) {
        printf("Pending task list is full!\n");
        return;
    }
    if (front == -1) front = 0;
    strcpy(pending[++rear], task);
    printf("Task added: %s\n", task);
}

// Dequeue function
void completeTask() {
    if (front == -1 || front > rear) {
        printf("No pending tasks!\n");
        return;
    }
    // Push completed task to stack
    if (top == MAX - 1) {
        printf("Completed task stack is full!\n");
        return;
    }
    strcpy(completed[++top], pending[front]);
    printf("Task completed: %s\n", pending[front]);
    front++;
}

// Undo last completed task
void undoTask() {
    if (top == -1) {
        printf("No completed tasks to undo!\n");
        return;
    }
    if (rear == MAX - 1) {
        printf("Pending task list is full!\n");
        return;
    }
    strcpy(pending[++rear], completed[top]);
    printf("Undo task: %s\n", completed[top]);
    top--;
}

// View pending tasks
void viewPending() {
    if (front == -1 || front > rear) {
        printf("No pending tasks!\n");
        return;
    }
    printf("\nPending Tasks:\n");
    for (int i = front; i <= rear; i++) {
        printf("%d. %s\n", i - front + 1, pending[i]);
    }
}

// View completed tasks
void viewCompleted() {
    if (top == -1) {
        printf("No completed tasks!\n");
        return;
    }
    printf("\nCompleted Tasks:\n");
    for (int i = top; i >= 0; i--) {
        printf("%d. %s\n", top - i + 1, completed[i]);
    }
}

int main() {
    int choice;
    char task[STR_LEN];

    while (1) {
        printf("\n--- Task Manager ---\n");
        printf("1. Add Task\n");
        printf("2. Complete Task\n");
        printf("3. Undo Last Completed Task\n");
        printf("4. View Pending Tasks\n");
        printf("5. View Completed Tasks\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // to consume newline

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(task, STR_LEN, stdin);
                task[strcspn(task, "\n")] = '\0'; // remove newline
                addTask(task);
                break;
            case 2:
                completeTask();
                break;
            case 3:
                undoTask();
                break;
            case 4:
                viewPending();
                break;
            case 5:
                viewCompleted();
                break;
            case 6:
                printf("Exiting Task Manager...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
