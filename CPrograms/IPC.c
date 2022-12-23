// A simple C program for user defined signals used for interprocess communicaton

// Name: Ian Peter Limo
// Student Number: SCT211-0036/2018

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int x = 0;
void handle_sigusr1(int sig) { // function that will provide hint to user if x value remains unchanged after 5s
  if (x == 0){
  printf("(HINT) Remember that the values can be broken down further for easier addition 5 + 5 + 5\n");
  }
}
int main (void) {
  int pid = fork();

  if (pid == 0) {
    // Child process providing hint if user lacks answer after 5s
    sleep(5);
    kill(getppid(), SIGUSR1);
  } else {

    signal(SIGUSR1, handle_sigusr1); // Using user-defined function
    // Parent process
    printf("Find sum of 10 and 5: \n");
    scanf("%d", &x);
    if (x == 15) {
      wait(NULL);
      printf("Right!\n");
    } else {
      printf("Wrong\n");
    }
    
    wait(NULL);
  }

  return 0;
}
