// Simple C program that gets process information of currently running processes
// This includes PID, priorities and PPID

//compiled using the following command
//gcc readps.c -o readps -lprocps

#include <stdio.h>
#include <string.h>
#include <proc/readproc.h>

int main(void)
{
      PROCTAB *proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS); // Creating PROCTAB Structure to use for readproc() function

      proc_t proc_info; // Creating process data type
      memset(&proc_info, 0, sizeof(proc_info)); // Creating section in memory to store process data
      printf("Program\tPID\tPPID\tPriority \n");

      while (readproc(proc, &proc_info) != NULL) {
          printf("%s\t%d\t%d\t%ld\n",proc_info.cmd, proc_info.tid, proc_info.ppid, proc_info.priority);
        } // Iterating through and printing process info using readproc() function

      closeproc(proc); // Freeing up memory created by using closeproc() function

      return 0;
}
