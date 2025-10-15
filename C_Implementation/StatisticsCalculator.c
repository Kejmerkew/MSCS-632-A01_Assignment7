#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
double calculateMean(int arr[], int n);
double calculateMedian(int arr[], int n);
void calculateMode(int arr[], int n);
void sortArray(int arr[], int n);

int main() {
    int n, choice;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input. Number of elements must be positive.\n");
        return 1;
    }

    int *arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nChoose input method:\n");
    printf("1. Enter numbers manually\n");
    printf("2. Generate random numbers\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nEnter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
    } else if (choice == 2) {
        int lower, upper;
        printf("Enter lower bound for random numbers: ");
        scanf("%d", &lower);
        printf("Enter upper bound for random numbers: ");
        scanf("%d", &upper);

        if (lower >= upper) {
            printf("Invalid range. Lower bound must be less than upper bound.\n");
            free(arr);
            return 1;
        }

        srand(time(NULL)); // seed random generator
        printf("\nGenerated numbers: ");
        for (int i = 0; i < n; i++) {
            arr[i] = (rand() % (upper - lower + 1)) + lower;
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Invalid choice.\n");
        free(arr);
        return 1;
    }

    sortArray(arr, n);

    printf("\nSorted List: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    double mean = calculateMean(arr, n);
    double median = calculateMedian(arr, n);

    printf("\n\nMean: %.2f", mean);
    printf("\nMedian: %.2f", median);
    printf("\nMode: ");
    calculateMode(arr, n);

    free(arr);
    return 0;
}

void sortArray(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double calculateMean(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double) sum / n;
}

double calculateMedian(int arr[], int n) {
    if (n % 2 == 0)
        return (arr[n/2 - 1] + arr[n/2]) / 2.0;
    else
        return arr[n/2];
}

void calculateMode(int arr[], int n) {
    int maxCount = 0;
    int currentCount = 1;
    int foundMode = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
            }
            currentCount = 1;
        }
    }
    if (currentCount > maxCount)
        maxCount = currentCount;

    currentCount = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            currentCount++;
        } else {
            if (currentCount == maxCount && maxCount > 1) {
                printf("%d ", arr[i - 1]);
                foundMode = 1;
            }
            currentCount = 1;
        }
    }

    if (currentCount == maxCount && maxCount > 1) {
        printf("%d", arr[n - 1]);
        foundMode = 1;
    }

    if (!foundMode)
        printf("No mode (all values occur equally).");
    printf("\n");
}
