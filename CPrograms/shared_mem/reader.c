// C program used in conjuction with writer.c to implement interprocess communication using shared memory

// Shared memory, this is where a region of memory that is shared by cooperating processes is established
// Processes then exchange information by reading and writing data to the shared memory 
#include <stdio.h>
#include <sys/ipc.h> //Used for shmget() function
#include<sys/shm.h> //Used for shmget() function
#include<sys/types.h> //Used for shmat() function
#include<sys/shm.h> //Used for shmat() function


int main(void)
{
    printf("\t\t**We will demonstrate shared memory**\n");
    void *shared_mem;
    char buff[100];
    int shmid;
    shmid=shmget((key_t)1122, 1024, 0666);
    printf("Key of shared memory is %d\n",shmid);
    shared_mem=shmat(shmid,NULL,0); //process attached to shared memory segment.
    printf("Process attached at %p\n", shared_mem);
    printf("Data read from shared memory is : %s\n", (char *)shared_mem);
    return 0;
}