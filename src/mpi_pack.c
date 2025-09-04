#include <stdio.h>
#include <math.h>
#include "mpi.h"
#define TAM_BUF 100
#define TAM 10

int main (int argc, char** argv) {
int i, meu_ranque, num_procs;   /* Ranque e número de processos */
float a [TAM] ;                  /* Valor a ser enviado*/
float b[TAM];                    /* Valor a ser recebido */
char buffer [TAM_BUF];
int posicao=0;                   /* Ponteiro de Pack e Unpack */
int destino = 1;           
MPI_Status estado;
         
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (meu_ranque == 0) {
        for  (i = 0; i < TAM; i++) 
                a[i] = (float) i;
        MPI_Pack(a, TAM, MPI_FLOAT, buffer, TAM_BUF, &posicao, MPI_COMM_WORLD); 
        MPI_Bcast(buffer, TAM_BUF, MPI_PACKED, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Bcast(buffer, TAM_BUF, MPI_PACKED, 0, MPI_COMM_WORLD);
        MPI_Unpack(buffer, TAM_BUF, &posicao, &b, TAM, MPI_FLOAT, MPI_COMM_WORLD);
    }
       
    /* Imprime o resultado*/
    if (meu_ranque == destino) {
        for (i = 0; i < TAM; i++) 
            printf("Com b[%d] = %3.1f ", i, b[i]);
	printf("\n");
        fflush(stdout);
    }
    /* Finaliza o MPI */
    MPI_Finalize();
    return 0;
} 
