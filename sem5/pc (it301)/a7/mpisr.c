#include<mpi.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
	int size,myrank,x,i;
	int s[5],r[5];
	MPI_Status status;	

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

	if(myrank==0)
	{
		for(i=0;i<5;i++)
		{
			s[i] = i+1; // s={1,2,3,4,5}
			r[i] = 5-i; // r={5,4,3,2,1}
		}
		printf("Process %d of %d,sending the array s\n",myrank,size);
		MPI_Send(&s,5,MPI_INT,1,55,MPI_COMM_WORLD);
	}
	else if(myrank==1)
	{
		MPI_Recv(&r,5,MPI_INT,0,55,MPI_COMM_WORLD,&status);
		printf("Source %d Tag %d \n",status.MPI_SOURCE,status.MPI_TAG);
		for(i=0;i<5;i++)
		printf("Received Array r : %d\n",r[i]);
	}
	MPI_Finalize();
	return 0;
}