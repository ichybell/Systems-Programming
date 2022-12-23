// // C program used in conjuction with reader.c to implement interprocess communication using shared memory

// Shared memory, this is where a region of memory that is shared by cooperating processes is established
// Processes then exchange information by reading and writing data to the shared memory 
#include <stdio.h>
#include <sys/ipc.h> //Used for shmget() function
#include<sys/shm.h> //Used for smget() function
#include<sys/types.h> //Used for shmat() function
#include<sys/shm.h> //Used for shmat() function
#include <string.h>


int main(void)
{
    printf("\t\t**We will demonstrate shared memory**\n");
    void *shared_memory;
    char buff[100]; //Used to get data from user to write to shared memory
    int shmid;
    shmid=shmget((key_t)1122, 1024, 0666|IPC_CREAT); //creates shared memory segment with key 1122, having size of 1024 bytes and permissions set to read,write and execute for user,group and everyone
    printf("Key of shared memory is %d\n",shmid);
    shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
    printf("Process attached at %p\n",shared_memory); //this prints the address where the segment is attached
    printf("Enter some data to write to shared memory\n");
    read(0,buff,100); //get some input from user
    strcpy(shared_memory,buff); //data written to shared memory
    printf("You wrote: %s\n", (char *)shared_memory);
    return 0;
}