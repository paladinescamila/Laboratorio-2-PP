/*
Name: parallel.c
Version: 1.5

Made by:
- Camila Paladines Muñoz
- Juan Sebastian Reyes Leyton

Source code: https://gist.github.com/hackrio1/a11c8499ed68f5df6c30e53d1c3fe076
*/

#include "parallel.h"

List createList( int n ) {
    /*
    Input: The size n of the array that will be created.
    Description: This function create a List of n positions and return 
                 that array.
    Output: The n-array.
    */
    List ans;
    ans = (List)calloc( n, sizeof(T) );
    return ans;
}

List randomList( int n ) {
    /*
    Input: The size n of the array that will be created.
    Description: This function create a List of n positions where their values have
                 random values and return that array.
    Output: The n-array with random values.
    */
    List ans;
    ans = (List)calloc( n, sizeof(T) );

    srand(time(NULL));

    // Fill the positions with random values
    for(int i = 0; i < n; i++) {
        ans[i] = rand() % (MAX_SIZE + 1);
    }

    return ans;
}

void merge( int i, int j, int mid, List a, List aux ) {
    /*
    Input: The index i, j and mid, the list a and aux.
    Description: This function realice the process to merge the 
                 right size of the array (a[mid+1 .. j]) and the 
                 left size of the array (a[i .. mid]) in the aux 
                 array, then assign that values in the order obtained
                 in the aux array
    Complexity: O(i+j) 
    Ouput: None
    */

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
    /*
    Input: The index i and j, and the lists a and aux.
    Description: This function implemented the divide and conquer
                 strategy of merge sort algorithm. It consists in 
                 divide the array a in two middles, both are sorted,
                 then is merge both middles in the merge function.
    Complexity: O(n log n)
    Output: None
    */
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

int main(int argc, char** argv) {
    int n = 100000000, i, d, swap;

    MPI_Init(&argc, &argv);

    List a, aux;
    // double time, finish;
    
    a = randomList(n);
    aux = createList(n);
    
    // time = MPI_Wtime();
    merge_sort(0, n - 1, a, aux);
    // finish = MPI_Wtime();

    // printf("N:%d, %f s\n", n, finish - time);

    MPI_Finalize();
    
    return 0;
}