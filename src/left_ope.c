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

t_file  get_file(t_shell *sh)
{
    int i;
    int y;
    t_file  manager;

    i = 0;
    y = 0;
    while (sh->mt[++i])
    {
        if (sh->mt[i][0] == '>' && sh->mt[i + 1])
            manager.file[y++] = sh->mt[i + 1];
    }
    manager.file[y] = NULL;
    return (manager);
}

t_file  get_arg(t_shell *sh)
{
    int i;
    int y;
    t_file  manager;

    i = 0;
    y = 0;
    while (sh->mt[++i])
    {
        if (sh->mt[i - 1][0] == '>' && sh->mt[i])
            manager.arg[y++] = sh->mt[i];
    }
    manager.arg[y] = NULL;
    return (manager);
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
        char *path = "/bin/ls";
        char *args[] = { "ls", "-l", NULL };
        int fd = open("filewwww", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
            perror("open");
            return ;
        }
        dup2(fd, STDOUT_FILENO);
        if (execve(path, args, sh->env) == -1)
        {
            perror("execve falhou");
            exit(EXIT_FAILURE);
        }
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
    int y;
    t_file  manager;

    //manager = malloc(sizeof(t_file));
    // if (find_right_oper(sh->mt))
    //     right_oper(sh);
    manager = get_file(sh);
        y = -1;
    while (manager.file[++y])
        printf("file[%d] = %s\n", y, manager.file[y]);
    
}
