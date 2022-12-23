// A simple C program that uses fork() sys call to create a child process


#include <stdio.h>
#include <unistd.h>
 int main(void) {
       pid_t pid = fork(); // fork creates two processes and the process ID is returned to be stored in the pid_t variable
       if(pid == 0) {
         // This is the child process
           printf("Child => PPID: %d PID: %d\n", getppid(), getpid());
       }
       else {
         // This is the parent process
       printf("Parent => PID: %d\n", getpid());
       }

       return 0;
 }
