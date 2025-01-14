#include<stdio.h>
#include <math.h> 
#include "mpi.h"
int main (int argc, char *argv[]){	
int meu_ranque, num_procs, n=10000000; 
double mypi, pi, h, x, sum = 0.0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	h=1.0/(double) n;
	for (int i = meu_ranque +1; i <= n; i += num_procs){	
		x = h * ((double) i - 0.5);
		sum  += (4.0/(1.0 + x*x));
	}
	mypi = h* sum;
	MPI_Allreduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	printf ("valor aproximado de pi: %.16f \n", pi);
	MPI_Finalize( );
}
