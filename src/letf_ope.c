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

void  get_file(t_shell *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (sh->mt[++i])
    {
        if (sh->mt[i][0] == '>')
            sh->manager.file[j++] = sh->mt[i + 1];
    }
    sh->manager.file[j] = NULL;
}

void  get_dir(t_shell *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (sh->mt[++i])
    {
        if ((!ft_strncmp(sh->mt[i], ">", 1) &&  ft_strlen(sh->mt[i]) == 1) || (!ft_strncmp(sh->mt[i], ">>", 2) && ft_strlen(sh->mt[i]) == 2))
            sh->manager.redir[j++] = sh->mt[i];
    }
    sh->manager.redir[j] = NULL;
}

void  get_arg(t_shell *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (sh->mt[i])
    {
        if (sh->mt[i][0] != '>')
        {
            sh->manager.arg[j++] = sh->mt[i];
            i++;
        }
        else
            i += 2;
    }
    sh->manager.arg[j] = NULL;
    sh->mt = sh->manager.arg;
}

int check_built_in(t_shell *sh)
{
    if (!ft_strcmp(sh->mt[0], "export"))
		return (1);
	else if (!ft_strcmp(sh->mt[0], "echo"))
		return (1);
	else if (!ft_strcmp(sh->mt[0], "unset"))
		return (1);
	else if (!ft_strcmp(sh->mt[0], "pwd"))
		return (1);
	else if (!ft_strcmp(sh->mt[0], "env"))
		return (1);
	else if (!ft_strcmp(sh->mt[0], "cd"))
		return (1);
	else if (!ft_strcmp(sh->mt[0], "exit"))
        return (1);
    return (0);
}

void    right_oper(t_shell *sh) 
{
    int pid;
    int i;
    int fd;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return ;
    }
    if (pid == 0)
    {
        i = 0;
        while (sh->manager.file[i])
        {
            if (!ft_strncmp(sh->manager.redir[i], ">>", 2))
                fd = open(sh->manager.file[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
            else
                fd = open(sh->manager.file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (sh->manager.file[i + 1])
                close(fd);
            i++;
        }
        if (fd < 0)
        {
            perror("open");
            return ;
        }
        dup2(fd, STDOUT_FILENO);
        sh->redirect = 1;
        if (!check_built_in(sh))
            execut_cmd(sh);
        else
            check_command(sh);
        close(fd);
        exit(0);
    }
    else
        waitpid(pid, NULL, 0);
}

void    operators(t_shell *sh)
{
    sh->manager.control = 1;
    get_dir(sh);
    get_file(sh);
    get_arg(sh);
    right_oper(sh);
}
