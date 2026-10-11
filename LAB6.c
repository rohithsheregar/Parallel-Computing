#include<stdio.h>
#include<string.h>
#include<mpi.h>
int main(int argc,char*argv[]){
    int rank,size,data_send,data_recv=-1;
    int deadlock=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(size<2){
        if(rank==0){
            printf("This program requires at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }
    if(argc>1&&strcmp(argv[1],"deadlock")==0)deadlock=1;
    data_send=rank;
    if(deadlock){
        if(rank==0){
            printf("Deadlock demonstration: both processes call MPI_Ssend first\n");
            fflush(stdout);
        }
        if(rank==0){
            MPI_Ssend(&data_send,1,MPI_INT,1,0,MPI_COMM_WORLD);
            MPI_Recv(&data_recv,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }else if(rank==1){
            MPI_Ssend(&data_send,1,MPI_INT,0,0,MPI_COMM_WORLD);
            MPI_Recv(&data_recv,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
    }else{
        if(rank==0){
            MPI_Send(&data_send,1,MPI_INT,1,0,MPI_COMM_WORLD);
            MPI_Recv(&data_recv,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("Process 0 received message: %d\n",data_recv);
            fflush(stdout);
        }else if(rank==1){
            MPI_Recv(&data_recv,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("Process 1 received message: %d\n",data_recv);
            fflush(stdout);
            MPI_Send(&data_send,1,MPI_INT,0,0,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}
// Compile (x64 Native Tools Command Prompt): cl LAB6.c msmpi.lib
// Run: mpiexec -n 2 LAB6.exe (add the argument deadlock at the end to see the deadlock)
