#include <stdio.h>
#include <unistd.h>
int main() {
    pid_t pid, parent_pid;
    int fork;
    pid = fork;
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child process created\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getpid());
    } else {
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
    }
    return 1;
}
