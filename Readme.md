# Laboratory 2

## Made by

- Camila Paladines
- Juan Sebastian Reyes

## Description

In this folder was parallelized the Merge Sort algoritm, this algorithm was implemented to based on divide an conquer strategy. This algorithms takes the array, for example **A** and divide this array in two sections, the left and right side, this division is realized in the half of the array. Then, both halfs are calls recusively by the same function, and after those calls both are merge. Finally, when they are merge the result array already is sorted.

### Step 1

```C
::::C
 #!python hl_lines="3 4"
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

```
!!! note
    Esto es un ejemplo de nota (note, seealso).


## Process to compile

1. Open the ubuntu terminal.
2. Locates the laboratory folder and place yourself in it.
3. To compile any .c file you must do it of the following form:

    ```sh
    make compile FILE=file_name_without_the_extension
    ```
    An example of how to compile is next:

    ```sh
    make compile FILE=parallel
    ```
4. Next, to visualize the result:

    ```sh
    make run FILE=file_name_without_the_extension NP=number_of_processes
    ```
    An example of how to run is next:

    ```sh
    make run FILE=parallel NP=4
    ```
5. If you want to realice an analysis through Gprof, you must continue the next steps.

    ```sh
    make compile_pg FILE=parallel
    make run FILE=parallel NP=4
    ```
    Writing NP = 4 indicates that 4 processes will be created, this number is customizable. When in your folder exists a file with name gmon.out, you put the next code in the terminal:

    ```sh
    make compile_gprof FILE=parallel
    ```

    When finish the compilation of the above code, you can see the results of the analysis in the file analysis_(name of file that you had compiled).txt. For the above example that info is located in analysis_parallel.txt.

## Time

If you want visualize the runtime through *time*, you must put before run code the command *time*, the following form:

```sh
time make run FILE=name_of_file_that_you_had_compiled_before
```

For example (continue with the before compilation):

```sh
time make run FILE=parallel
```

By default, when you run the code, this show the `omp_get_wtime`.

## References

- [Merge Sort algorithm in C](https://gist.github.com/hackrio1/a11c8499ed68f5df6c30e53d1c3fe076)
- [Difference between malloc and calloc](https://cs-fundamentals.com/tech-interview/c/difference-between-malloc-and-calloc)