#include <iostream>
#include <mpi.h>
#include <vector>

#define MATRIX_DIMENSION 25

void matrix_mult(double *A, double *b, double *x, int rows, int cols) {
//    x = A * b
    for (int i = 0; i < rows; ++i) {
        x[i] = 0.0;
        for (int j = 0; j < cols; ++j) {
            x[i] = A[i * cols + j] * b[j];
        }
    }
}

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    int rank, nprocs;

//    cuantos procesos / ranks.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int ROWS_PER_RANK; // # de filas a enviar a cada RANK
    int ROWS_ALLOC; // tamaño ajustando de la matriz para que las filas son divisibles para NPROCS

    int padding = 0;
    if (MATRIX_DIMENSION % nprocs != 0) {
//        ajustar el tamaño de la matriz
        ROWS_ALLOC = std::ceil((double) MATRIX_DIMENSION / nprocs) * nprocs; // nprocs => 7 * 4 = 28
        padding = ROWS_ALLOC - MATRIX_DIMENSION; // 28 - 25 = 3
    }

    ROWS_PER_RANK = ROWS_ALLOC / nprocs; //valor ajustado => 28/4 = 7

//    x = A * b
    std::unique_ptr<double[]> A; //solicitar memoria y que sea automatica. (liberando memoria)
    std::unique_ptr<double[]> b = std::make_unique<double[]>(MATRIX_DIMENSION); //misma dimension
    std::unique_ptr<double[]> x;

//    Xi = Ai * b
    std::unique_ptr<double[]> A_local;
    std::unique_ptr<double[]> X_local;

    if (rank == 0) {
//        leer la matriz (configuracion)
        std::printf("Dimension: %d, ROWS_ALLOC: %d, ROWS_PER_RANK: %d, padding: %d\n", MATRIX_DIMENSION, ROWS_ALLOC,
                    ROWS_PER_RANK, padding);
        //inicializar matriz
        A = std::make_unique<double[]>(ROWS_ALLOC * MATRIX_DIMENSION);
        x = std::make_unique<double[]>(ROWS_ALLOC); //n + padding

//        inicializar matriz A
        for (int i = 0; i < MATRIX_DIMENSION; ++i) {
            for (int j = 0; j < MATRIX_DIMENSION; ++j) {
                int index = i * MATRIX_DIMENSION + j; // (0 - 24), (25 - 49), (50 - 74)... (600 - 624) = 24 indices
                A[index] = i; // A[0] = 0 a 24 elementos = zeros, A[1] = 25 a 49 elementos = ones, A[2] = 50 a 74 elementos, twos
            }
        }

//        inicializar vector b
        for (int i = 0; i < MATRIX_DIMENSION; ++i) {
            b[i] = i;
        }
    }

//    inicializar Ai, Xi
    A_local = std::make_unique<double[]>(ROWS_PER_RANK * MATRIX_DIMENSION);
    X_local = std::make_unique<double[]>(ROWS_PER_RANK);

//    enviar el vector b completo a todos los ranks
    MPI_Bcast(b.get(), MATRIX_DIMENSION, MPI_DOUBLE, 0, MPI_COMM_WORLD);

//    monton de sends o enviar la matriz A
    MPI_Scatter(A.get(), ROWS_PER_RANK * MATRIX_DIMENSION, MPI_DOUBLE, //envio
                A_local.get(), ROWS_PER_RANK * MATRIX_DIMENSION, MPI_DOUBLE, //recepcion
                0, MPI_COMM_WORLD);

    std::printf("RANK: %d %d elementos: start: %.0f, end: %0.f\n",
                rank, ROWS_PER_RANK * MATRIX_DIMENSION, A_local[0], A_local[ROWS_PER_RANK * MATRIX_DIMENSION - 1]);

//    ajustar => Xi = Ai * b
    int ROWS_PER_RANK_TMP = ROWS_PER_RANK;

    if (rank == nprocs - 1) ROWS_PER_RANK_TMP = ROWS_PER_RANK - padding;

    std::printf("RANK_%d\n A_local=%d x %d\n", rank, ROWS_PER_RANK_TMP, MATRIX_DIMENSION);

    //operacion de matriXmult
//                x[i] += A[i * cols + j] * b[j];
    matrix_mult(A_local.get(), b.get(), X_local.get(), ROWS_PER_RANK_TMP, MATRIX_DIMENSION);

//enviar pedazos
    MPI_Gather(X_local.get(), ROWS_PER_RANK, MPI_DOUBLE, //envio
               x.get(), ROWS_PER_RANK, MPI_DOUBLE, //recepcion
               0, MPI_COMM_WORLD);

//    imprimir resultado
    if (rank == 0) {
        std::printf("Resultado\n");
        for (int i = 0; i < MATRIX_DIMENSION; ++i) {
            std::printf("%.0f, ", x[i]);
        }
        std::cout << std::endl;
    }

    MPI_Finalize();

    return 0;
}
