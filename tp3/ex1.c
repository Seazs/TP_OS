#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        printf("Hello from the child process!\n");
        pid_t pid = getpid();
        printf("PID: %d\n", pid);//%d pour 
        pid_t ppid = getppid();
        printf("PPID: %d\n", ppid);//%d
    } else if (pid > 0){
        // Parent process
        printf("Hello from the parent process!\n");
        pid_t pid = getpid();
        printf("PID: %d\n", pid);
        pid_t ppid = getppid();
        printf("PPID: %d\n", ppid);//%d
    } else {
        // Error
        printf("Error while creating the child process!\n");
    }
}
