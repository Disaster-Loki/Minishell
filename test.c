# include <wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

int main(int ac, char **av, char *env[])
{
    int fd;

    fd = open("name.txt", O_APPEND | O_WRONLY, 0644);
    dup2(fd, STDOUT_FILENO);
    execve("/bin/ls", av, env);
    return (0);
}

