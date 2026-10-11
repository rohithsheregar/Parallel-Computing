#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(int argc,char**argv){
    int rank,size,recv;
    int*data;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    data=(int*)malloc(size*sizeof(int));
    if(rank==0){
        for(int i=0;i<size;i++)data[i]=10*(i+1);
    }
    MPI_Scatter(data,1,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Process %d received: %d\n",rank,recv);
    fflush(stdout);
    recv+=1;
    MPI_Gather(&recv,1,MPI_INT,data,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("Gathered data: ");
        for(int i=0;i<size;i++)printf("%d ",data[i]);
        printf("\n");
    }
    free(data);
    MPI_Finalize();
    return 0;
}
// Compile (x64 Native Tools Command Prompt): cl LAB8.c msmpi.lib
// Run: mpiexec -n 4 LAB8.exe
