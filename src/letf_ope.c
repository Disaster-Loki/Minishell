#include "../inc/minishell.h"

int find_right_oper(char **mt)
{
    int	i;

	i = -1;
	while (mt[++i])
	{
		if (mt[i][0] == '>')
			return (1);
	}
	return (0);
}

void    right_oper(t_shell *sh) 
{
    int pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return ;
    }
    if (pid == 0)
    {
        int fd = open("filewwww", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
            perror("open");
            return ;
        }
        dup2(fd, STDOUT_FILENO);
        sh->redirect = 1;
        check_command(sh);
        close(fd);

        exit(0);
    }
    else
        waitpid(pid, NULL, 0);
}

void    operators(t_shell *sh)
{
    if (find_right_oper(sh->mt))
        right_oper(sh);
}
