#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int main(int argc, char** argv) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Inicio de medición paralela
    double t_inicio = MPI_Wtime();

    int chunk = N / size;
    long long *arr = NULL;
    if (rank == 0) {
        arr = (long long*) malloc(N * sizeof(long long));
        for (int i = 0; i < N; i++) arr[i] = i;
    }

    long long *local = (long long*) malloc(chunk * sizeof(long long));
    MPI_Scatter(arr, chunk, MPI_LONG_LONG, local, chunk, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    long long suma_local = 0;
    #pragma omp parallel for reduction(+:suma_local)
    for (int i = 0; i < chunk; i++) suma_local += local[i];

    long long suma_total = 0;
    MPI_Reduce(&suma_local, &suma_total, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double t_fin = MPI_Wtime();

    if (rank == 0) {
        double t_paralelo = t_fin - t_inicio;
        printf("Suma total: %lld | Tiempo paralelo: %.4f s\n", suma_total, t_paralelo);

        // Versión Secuencial
        long long suma_seq = 0;
        double ts = MPI_Wtime();
        for (int i = 0; i < N; i++) suma_seq += i;
        double te = MPI_Wtime();
        double t_secuencial = te - ts;

        printf("Tiempo secuencial: %.4f s\n", t_secuencial);
        printf("Speedup: %.2fx\n", t_secuencial / t_paralelo);
        
        free(arr);
    }

    free(local);
    MPI_Finalize();
    return 0;
}