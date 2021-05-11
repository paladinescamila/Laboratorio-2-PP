# Laboratory 2

## Made by

- Camila Paladines
- Juan Sebastian Reyes

## Description

In this folder was parallelized the mergesort algoritm

## Process to compile

1. Open the ubuntu terminal.
2. Locates the laboratory folder and place yourself in it.
3. To compile any .c file you must do it of the following form:

    ```sh
    make compile FILE=name_file_without_the_extension
    ```
   An example of how to compile is next:

    ```sh
    make compile FILE=parallel
    ```
4. Next, to visualize the result:

    ```sh
    make run FILE=paralleL
    ```
5. If you want to realice an analysis though Gprof, you must continue the next steps.

    ```sh
    make compile_pg FILE=parallel
    make run FILE=parallel
    ```
    When in your folder exists a file with name gmon.out, you put the next code in the terminal

    ```sh
    make compile_gprof FILE=parallel
    ```

    When finish the compilation of the above code, you can see the results of the analysis in the file Analysis_(name of file that you had compiled).txt. For the above example that info is located in Analysus_parallel.txt.

## References

- https://gist.github.com/hackrio1/a11c8499ed68f5df6c30e53d1c3fe076
- https://cs-fundamentals.com/tech-interview/c/difference-between-malloc-and-calloc