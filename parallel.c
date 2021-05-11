/*
Name: parallel.c
Version: 1.3

Made by:
- Camila Paladines Muñoz
- Juan Sebastian Reyes Leyton
*/

#include "parallel.h"

List createList( int n ) {
    List ans;
    ans = (List)calloc( n, sizeof(T) );
    return ans;
}

List randomList( int n ) {
    List ans;
    ans = (List)calloc( n, sizeof(T) );

    srand(time(NULL));

    for(int i = 0; i < n; i++) {
        ans[i] = rand() % (MAX_SIZE + 1);
    }

    return ans;
}

void merge( int i, int j, int mid, List a, List aux ) {
    int pointer_left = i;       // pointer_left points to the beginning of the left sub-array
    int pointer_right = mid + 1;        // pointer_right points to the beginning of the right sub-array
    int k;      // k is the loop counter

    // we loop from i to j to fill each element of the final merged array
    for (k = i; k <= j; k++) {
        if (pointer_left == mid + 1) {      // left pointer has reached the limit
            aux[k] = a[pointer_right];
            pointer_right++;
        } else if (pointer_right == j + 1) {        // right pointer has reached the limit
            aux[k] = a[pointer_left];
            pointer_left++;
        } else if (a[pointer_left] < a[pointer_right]) {        // pointer left points to smaller element
            aux[k] = a[pointer_left];
            pointer_left++;
        } else {        // pointer right points to smaller element
            aux[k] = a[pointer_right];
            pointer_right++;
        }
    }

    for (k = i; k <= j; k++) {      // copy the elements from aux[] to a[]
        a[k] = aux[k];
    }
}

// function to sort the subsection a[i .. j] of the array a[]
void merge_sort(int i, int j, List a, List aux) {
    if (j <= i) {
        return;     // the subsection is empty or a single element
    }
    int mid = (i + j) / 2;

    // left sub-array is a[i .. mid]
    // right sub-array is a[mid + 1 .. j]
    
    merge_sort(i, mid, a, aux);     // sort the left sub-array recursively
    merge_sort(mid + 1, j, a, aux);     // sort the right sub-array recursively
    merge(i, j, mid, a, aux);
}

int main() {
    int n = 100000000, i, d, swap;
    List a, aux;
    double time, finish;
    
    a = randomList(n);
    aux = createList(n);
    
    time = omp_get_wtime();
    merge_sort(0, n - 1, a, aux);
    finish = omp_get_wtime();


    printf("N:%d, %f s\n", n, finish - time);
    
    return 0;
}