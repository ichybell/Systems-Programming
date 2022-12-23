// A C prpgram that creates a child process and 
// uses wait() sys call to suspend parent process

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

 int main(void) {
       pid_t pid = fork(); // We create a child and parent process
       int status;

       if(pid == 0) {
           printf("Child => PPID: %d PID: %d\n", getppid(), getpid());
       }

       else {
       printf("Parent => PID: %d\n", getpid());
       wait(&status); // wait() sys call is used which blocks current process until child process exits or signal is received

       // We expect code execution to continue only after the child process has returned

       if (WIFEXITED(status) == 1){ // WIFEXITED returns if child exited normally
       printf("The Child has now exited successfully"); //This part will print only after the child process has terminated
       }
       else if (WIFSIGNALED(status)){ // WIFSIGNALED returns if child exited because a signal was not caught
           psignal(WTERMSIG(status), "Error with exit signal");   // WTERMSIG gives the number of the terminating signal
       }
     }

       return 0;
 }
