#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 10000;  // Número de términos en la serie
    int series[n];
    int start = rank * n / size;
    int end = (rank + 1) * n / size;
    int vardos = 1;

    for (int i = 1; i < end; i++) {
        if (i % 2 == 0) {
            series[i] = i;
        } else {
            series[i] = (vardos*vardos)+1;
            vardos = vardos+1;
        }
    }

    int *result = NULL;
    if (rank == 0) {
        result = (int *)malloc(n * sizeof(int));
    }

    MPI_Gather(series + start, end - start, MPI_INT, result, end - start, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Serie generada con MPI:\n");
        for (int i = 1; i < n; i++) {
            printf("%d, ", result[i]);
        }
        printf("\n");
        free(result);
    }

    MPI_Finalize();
    return 0;
}
