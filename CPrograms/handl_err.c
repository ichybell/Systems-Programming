// A simple C program for user defined signals

// Name: Ian Peter Limo
// Student Number: SCT211-0036/2018

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void handle_sig(int sig)
{
  printf ("SIGINT (%d) caught. Now exiting program....\n", sig);
  exit(0);
}

int main(void)
{
  signal(SIGINT, handle_sig);
  while (1)
    {
      printf ("Not yet caught. Stil running....\n\n");
      sleep (1);
    }

  return 0;
}
