#include<iostream>
#include<mpi.h>
using namespace std;
using namespace MPI;

//Use a for-loop to implement this ring implementation
// Assuming there are n processes, the proc 0 ---> proc 1 ---> proc 2 ....... proc n-1 ---> proc 0
int main(int argc, char ** argv)
{
    Init();
    int num_procs = COMM_WORLD.Get_size();
    for (int i=0; i<num_procs; i++)
    {
        if(COMM_WORLD.Get_rank()==i)
        {   
            int rank_send = i;
            int tag = 20;
            int recv_rank = (i+1)%num_procs; // Rank of the receiving process
            COMM_WORLD.Send(&rank_send, 1, INT, recv_rank, tag);
        }

        if(COMM_WORLD.Get_rank()==(i+1)%num_procs)
        {  
            int rank_recv;
            int tag_new = 20;
            int send_rank = (i + 1) % num_procs;
            COMM_WORLD.Recv(&rank_recv, 1, INT, i , tag_new);
            cout<<"Process "<< send_rank<< " received from "<< rank_recv<<"\n";
        }
    }
    Finalize();
    return 0;
}
