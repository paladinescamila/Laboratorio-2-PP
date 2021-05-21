/*
Name: parallel.c
Version: 1.5

Made by:
- Camila Paladines Muñoz
- Juan Sebastian Reyes Leyton

Source code: https://gist.github.com/hackrio1/a11c8499ed68f5df6c30e53d1c3fe076
*/

#include "parallel.h"
#include <math.h>

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
    int n = 25, i, d, swap = 123, swap1, rank, nproc;
    double start, end;
    List a, aux;

    a = randomList(n);
    aux = createList(n);

    for (i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n");

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int m = n/nproc, ac = 0;
    int displacements[nproc], counts[nproc];
    List ap, auxp;

    int temp = n % nproc;
    for (i = 0; i < nproc; i++){
        counts[i] = (i < temp) ? (n/nproc)+1 : (n/nproc);
        if (i > 0){
            displacements[i] = displacements[i-1]+counts[i-1];
        }
        else{
            displacements[i] = 0;
        }
    }
    ap = createList(counts[rank]);
    auxp = createList(counts[rank]);

    MPI_Scatterv(a, counts, displacements, MPI_INT, ap, counts[rank], MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("RANK: %d\n", rank);
    for (i = 0; i < counts[rank]; i++)
        printf("%d ", ap[i]);
    printf("\n");

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    merge_sort(0, counts[rank]-1, ap, auxp);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("RANK MERGE: %d\n", rank);
    for (i = 0; i < counts[rank]; i++)
            printf("%d ", ap[i]);
        printf("\n");

    List a1;
    if (rank == 0){
        a1 = createList(n);
        for (i = 0; i < n; i++)
            a1[i] = a[i];
    }

    printf("COUNTS\n");
    for (i = 0; i < nproc; i++){
            printf("%d ", counts[i]);
    }
    printf("\n");

    printf("DISPLACEMENTS\n");
    for (i = 0; i < nproc; i++){
            printf("%d ", displacements[i]);
    }
    printf("\n");

    MPI_Gatherv(ap, counts[rank], MPI_INT, a1, counts, displacements, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("RANK a1: %d\n", rank);
    for (i = 0; i < n; i++)
            printf("%d ", a1[i]);
    printf("\n");

    if (rank == 0){

        if (nproc == 2){
            merge(0, n-1, counts[0], a1, aux);
        }
        else if (nproc == 3){
            merge(0, counts[0]+counts[1]-2, counts[0], a1, aux);
            merge(0, n-1, counts[0]+counts[1]-2, a1, aux);
        }
        else if (nproc == 4){
            merge(0, (n-1)/2, (n-1)/4, a1, aux);
            merge((n-1)/2, n-1, 3*(n-1)/4, a1, aux);
            merge(0, n-1, (n-1)/2, a1, aux);
        }

        // merge(0, n-1, (n-1)/2, a1, aux);

        for (i = 0; i < n; i++)
            a[i] = a1[i];
    }

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    MPI_Finalize();

    if (rank == 0){
        printf("N:%d, %f s\n", n, end - start);
        for (i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n");
    }
    
    return 0;
}