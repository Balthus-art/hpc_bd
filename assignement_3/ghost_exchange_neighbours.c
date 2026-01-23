/******************************************************************************
* FILE: ghost_exchange_neighbours.c
* DESCRIPTION: 
*   This program has two functions:
*   1) Get the neighbouring ranks of each process in a 2D Cartesian topology.
*   2) Exchange ghost cells with these neighbouring ranks.
******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int *get_nbours (int pid, int m, int n)
{
  int *neighbours = (int *)malloc(4 * sizeof(int));
  for (int i = 0; i < 4; i++) {
    neighbours[i] = -1;
  }

  neighbours[0] = pid % n == 0 ? -1 : pid - 1;
  neighbours[1] = pid % n == n - 1 ? -1 : pid + 1;
  neighbours[2] = pid < n ? -1 : pid - n;
  neighbours[3] = pid >= (m - 1) * n ? -1 : pid + n;

  return neighbours;
}





// int main (int argc, char *argv[])
// {
// int numtasks, rank, dest, tag, source, rc, count;
// char inmsg, outmsg='x';
// MPI_Status Stat;

// MPI_Init(&argc,&argv);
// MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
// MPI_Comm_rank(MPI_COMM_WORLD, &rank);
// printf("Task %d starting...\n",rank);

// if (rank == 0) {
//   if (numtasks > 2) 
//     printf("Numtasks=%d. Only 2 needed. Ignoring extra...\n",numtasks);
//   dest = rank + 1;
//   source = dest;
//   tag = rank;
//   rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
//   printf("Sent to task %d...\n",dest);
//   rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
//   printf("Received from task %d...\n",source);
//   }

// else if (rank == 1) {
//   dest = rank - 1;
//   source = dest;
//   tag = rank;
//   rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
//   printf("Received from task %d...\n",source);
//   rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
//   printf("Sent to task %d...\n",dest);
//   }

// if (rank < 2) {
//   rc = MPI_Get_count(&Stat, MPI_CHAR, &count);
//   printf("Task %d: Received %d char(s) from task %d with tag %d \n",
//          rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
//   }

// MPI_Finalize();
// }