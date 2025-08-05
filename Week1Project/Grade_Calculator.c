// C Program: Grade Calculator for Multiple Students.

#include <stdio.h>
#include <string.h>

int main() {
    int i, n;
    char name[50];
    float math, english, science;
    float total, average;
    char grade;

    printf("How many students? ");
    scanf("%d", &n);
    getchar();  // clear newline from buffer after scanf

    for (i = 1; i <= n; i++) {
        printf("\n--- Enter details for Student %d ---\n", i);

        printf("Enter student name: ");
        fgets(name, sizeof(name), stdin);

        printf("Enter marks for Math: ");
        scanf("%f", &math);

        printf("Enter marks for English: ");
        scanf("%f", &english);

        printf("Enter marks for Science: ");
        scanf("%f", &science);
        getchar(); // clear newline

        // Validate marks
        if ((math < 0 || math > 100) || (english < 0 || english > 100) || (science < 0 || science > 100)) {
            printf("Error: Marks should be between 0 and 100.\n");
            i--; // repeat this iteration
            continue;
        }

        total = math + english + science;
        average = total / 3;

        if (average >= 90) grade = 'A';
        else if (average >= 80) grade = 'B';
        else if (average >= 70) grade = 'C';
        else if (average >= 60) grade = 'D';
        else grade = 'F';

        // Display result
        printf("\n--- Report for Student %d ---\n", i);
        printf("Name: %s", name);
        printf("Total Marks: %.2f\n", total);
        printf("Average Marks: %.2f\n", average);
        printf("Grade: %c\n", grade);
    }

    return 0;
}
