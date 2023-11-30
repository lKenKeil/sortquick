#include <stdio.h>
#include <stdlib.h>
# include <time.h>

// 두 요소를 교환하는 함수
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// 배열을 분할하고 피벗 인덱스를 반환하는 함수
int partition(int arr[], int low, int high, int* comparisons, int* moves) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            (*moves)++;
            swap(&arr[i], &arr[j]);
        }
    }
    (*moves)++;
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// 반복적인 퀵 소트를 구현하는 함수
void iterativeQuickSort(int arr[], int low, int high, int* comparisons, int* moves) {
    int stack[high - low + 1];
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pivotIndex = partition(arr, low, high, comparisons, moves);

        if (pivotIndex - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }

        if (pivotIndex + 1 < high) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}

int main() {
    srand(time(NULL));

    int iterations = 20;
    int totalComparisons = 0;
    int totalMoves = 0;

    for (int iter = 0; iter < iterations; iter++) {
        int arr[20];

        for (int i = 0; i < 20; i++) {
            arr[i] = rand() % 100;
        }

        printf("\n%d번째 반복:\n", iter + 1);

        int comparisons = 0;
        int moves = 0;

        iterativeQuickSort(arr, 0, 19, &comparisons, &moves);

        printf("정렬된 배열: ");
        for (int i = 0; i < 20; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        printf("비교 횟수: %d\n", comparisons);
        printf("이동 횟수: %d\n", moves);

        totalComparisons += comparisons;
        totalMoves += moves;
    }

    printf("\n평균 비교 횟수: %.2f\n", (float)totalComparisons / iterations);
    printf("평균 이동 횟수: %.2f\n", (float)totalMoves / iterations);

    return 0;
}
