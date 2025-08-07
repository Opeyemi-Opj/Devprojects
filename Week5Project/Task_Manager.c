
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    char name[50];
    struct Task* next;
} Task;

Task* taskQueue = NULL; // FIFO
Task* undoStack = NULL; // LIFO

void enqueue(char* taskName) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    strcpy(newTask->name, taskName);
    newTask->next = NULL;

    if (taskQueue == NULL) {
        taskQueue = newTask;
    } else {
        Task* temp = taskQueue;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newTask;
    }
}

void dequeue() {
    if (taskQueue == NULL) {
        printf("No tasks to complete.");
        return;
    }
    Task* temp = taskQueue;
    taskQueue = taskQueue->next;
    printf("Completed Task: %s\n", temp->name);
    free(temp);
}

void pushUndo(char* taskName) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    strcpy(newTask->name, taskName);
    newTask->next = undoStack;
    undoStack = newTask;
}

void undoLast() {
    if (undoStack == NULL) {
        printf("No tasks to undo.\n");
        return;
    }
    char taskToUndo[50];
    strcpy(taskToUndo, undoStack->name);

    // Remove from undo stack
    Task* tempUndo = undoStack;
    undoStack = undoStack->next;
    free(tempUndo);

    // Remove task from queue (from end)
    if (taskQueue == NULL) return;

    Task* current = taskQueue;
    Task* prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        // Only one task in queue
        taskQueue = NULL;
    } else {
        prev->next = NULL;
    }

    printf("Undone Task: %s\n", taskToUndo);
    free(current);
}

void showTasks() {
    if (taskQueue == NULL) {
        printf("No tasks in the queue.\n");
        return;
    }
    printf("Tasks in queue:\n");
    Task* temp = taskQueue;
    while (temp != NULL) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
}

int main() {
    int choice;
    char task[50];

    do {
        printf("\n1. Add Task\n2. View Tasks\n3. Complete Task\n4. Undo Last Add\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter Task: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = 0;
                enqueue(task);
                pushUndo(task);
                break;
            case 2:
                showTasks();
                break;
            case 3:
                dequeue();
                break;
            case 4:
                undoLast();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
