#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int provided;
    // Se usa MPI_THREAD_FUNNELED para que solo el hilo principal haga llamadas MPI
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // TODO 1: Región paralela OpenMP con 4 hilos
    #pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        printf("  Proceso MPI %d | Hilo OpenMP %d de %d\n", rank, tid, nthreads);
    }

    // TODO 2: Cálculo de unidades de cómputo totales
    if (rank == 0) {
        int hilos_por_proceso = 4; 
        printf("Total unidades: %d x %d = %d\n", size, hilos_por_proceso, size * hilos_por_proceso);
    }

    MPI_Finalize();
    return 0;
}