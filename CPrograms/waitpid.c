// A C prpgram that creates a child process and 
// uses waitpid() sys call to suspend parent process


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

 int main(void) {
       pid_t pid[3]; // Created three pid_t variables
       int status,i;
       for (i=0 ; i < 3; i++)
       {
           if(pid[i] = fork() == 0) {
               sleep(1);
               exit(10 + i);
               }
       } // Creating three child processes which wait 1 second between creating and return with a specific exit code for each child process

       // Using waitpid() and exit codes to see each child process
       for (i =0; i < 3; i++)
       {
           pid_t wpid = waitpid(pid[i] , &status, 0); // Each child pid is passed, 0 refers to no option i.e. parent has to wait for child to terminate
           if (WIFEXITED(status)) // // WIFEXITED returns if child exited normally
           {
               printf("Child process %d has terminated successfully with exit code: %d\n", wpid, WEXITSTATUS(status));
               // WEXITSTATUS returns code when child exits. Each child will have its own exit code.
           }
       }
       return 0;
 }
