// A simple C program for user defined signals for mutliple handlers

// This will demonstrate how user defines specific handling of 3 signals
// SIGINT, SIGUSR1, SIGUSR2


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

int x= 10;

void handler_1(int sig){
    x+=10;
    printf("Handler_1 starts off with x as %d\n",x);
}

void handler_2(int sig){
    x+=15;
    printf("Handler_2 has taken over with x set to %d\n", x);
}

void handler_3(int sig){
    x+=20;
    printf("Handler_3 closes the day setting the value of x to %d\n", x);
}

int main(){
    signal(SIGINT, handler_1);
    signal(SIGUSR1, handler_2);
    signal(SIGUSR2, handler_3);
    pid_t pid = fork();

    if(pid==0){
        pid_t parent = getppid();
        kill(parent , SIGINT);
        sleep(2);
        kill(parent, SIGUSR1);
        sleep(2);
        kill(parent, SIGUSR2);
        sleep(2);
        printf("In child process, x is still %d",x);
        return 0;
    }else {
        int status;
        wait(&status);
    }
    return 0;
}
