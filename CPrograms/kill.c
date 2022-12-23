// A simple C program that terminates any process provided

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


int main(int argc, char *agrv[])
{
    pid_t pid; //pid_t variable to store process ID
    printf("Please input your process ID\n\n");
    scanf("%d", &pid);
    if (pid){
        printf("Success!\nThe Process with PID %d has been terminated", pid);
        kill (pid, SIGKILL); //Sending a kill signal to running process
    }
    else {
        printf("Fail!\nPlease input correct PID");
        return 1;
    } // if else condition to check if a PID has been provided
    return 0;
}
