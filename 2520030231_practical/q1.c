#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Before fork: PID = %d, PPID = %d\n", getpid(), getppid());

    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("\n[CHILD] Running state\n");
        printf("[CHILD] PID  = %d\n", getpid());
        printf("[CHILD] PPID = %d\n", getppid());
        printf("[CHILD] Doing some work...\n");
        sleep(3);  // Simulate work -> Running/Waiting state
        printf("[CHILD] Work done. Terminating.\n");
        exit(0);   // Child becomes Terminated (zombie until parent reaps it)
    }
    else {
        // Parent process
        printf("\n[PARENT] PID  = %d\n", getpid());
        printf("[PARENT] Child PID = %d\n", pid);
        printf("[PARENT] Waiting for child to finish...\n");

        int status;
        wait(&status);  // Parent enters Waiting state until child terminates

        if
