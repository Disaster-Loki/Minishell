#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    int fd;

    fd = open("output.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    dup2(fd, STDOUT_FILENO);
    printf("Just believe\n");
    // char *args[] = {"/bin/ls", NULL};
    // if (execve("/bin/ls", args, envp) < 0)
    // {
    //     perror("execve");
    //     exit(EXIT_FAILURE);
    // }
    return 0;
}