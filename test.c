#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int ac, char *av[], char *env[])
{
    int fd;

    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (!fd)
    {
        perror("error\n");
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    printf("The text is well done!\n");
    return (0);
}

