#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);          // Inicializar MPI
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // ID de este proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Total de procesos
    
    // TODO 1: Imprime rank y size desde CADA proceso
    printf("Proceso %d de %d: ¡Hola desde MPI!\n", rank, size);


    // TODO 1: Imprime rank y size desde CADA proceso
    if (rank == 0) {
        printf("[MAESTRO] Todos los %d procesos han saludado.\n", size);
    }
    MPI_Finalize();                  // Cerrar MPI
    return 0;
}

