#include <stdio.h>

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        // Last i elements are already in place
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Function to perform linear search
int linearSearch(int arr[], int n, int target) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == target) {
            return i;  // Return the index of the found item
        }
    }
    return -1;  // Not found
}

int main() {
    int arr[100], n, target;

    // Get number of elements from user
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Get array elements from user
    printf("Enter %d numbers:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    bubbleSort(arr, n);

    // Display sorted array
    printf("\nSorted array:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Ask user for value to search
    printf("Enter a number to search for: ");
    scanf("%d", &target);

    // Search for the number
    int index = linearSearch(arr, n, target);

    // Show search result
    if(index != -1) {
        printf("%d found at position %d (index %d).\n", target, index + 1, index);
    } else {
        printf("%d not found in the list.\n", target);
    }

    return 0;
}
