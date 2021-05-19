#ifndef PARALLEL_H
#define PARALLEL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi/mpi.h>
#include <omp.h>

#define MAX_SIZE 100

typedef int T;
typedef T* List;

List createList( int );
List randomList( int );

#endif