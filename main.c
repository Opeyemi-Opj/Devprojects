// C Program: Grade Calculator for Multiple Students using custom input_utils.h

#include <stdio.h>
#include "include/input_utils.h"

int main() {
    int n = get_int("How many students? ");

    for (int i = 1; i <= n; i++) {
        printf("\n--- Enter details for Student %d ---\n", i);

        string name = get_string("Enter student name: ");
        float math = get_float("Enter marks for Math: ");
        float english = get_float("Enter marks for English: ");
        float science = get_float("Enter marks for Science: ");

        // Validate marks
        if ((math < 0 || math > 100) || (english < 0 || english > 100) || (science < 0 || science > 100)) {
            printf("Error: Marks should be between 0 and 100.\n");
            i--;
            continue;
        }

        float total = math + english + science;
        float average = total / 3;
        char grade;

        if (average >= 90) grade = 'A';
        else if (average >= 80) grade = 'B';
        else if (average >= 70) grade = 'C';
        else if (average >= 60) grade = 'D';
        else grade = 'F';

        printf("\n--- Report for Student %d ---\n", i);
        printf("Name: %s\n", name);
        printf("Total Marks: %.2f\n", total);
        printf("Average Marks: %.2f\n", average);
        printf("Grade: %c\n", grade);
    }

    return 0;
}
