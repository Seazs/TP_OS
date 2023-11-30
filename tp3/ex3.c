#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    pid_t pid = fork();
    int status;
    if (pid > 0) {
        // Parent process
        printf("Hello from the parent process!\n");
        printf("PID: %d\t", getpid());
        printf("PPID: %d\n", getppid());//%d
        if(waitpid(pid, &status, 0) < 0){
            perror("waitpid()");
            return 1;
        }
        if (WIFEXITED(status)){
            printf("Child process exited with code %d\n", WEXITSTATUS(status));
        }
        
    } else if (pid == 0){
        // Child process
        printf("Hello from the child process!\n");
        printf("PID: %d\t", getpid());//%d pour 
        printf("PPID: %d\n", getppid());//%d
    } else {
        // Error
        printf("Error while creating the child process!\n");
    }
}
