/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 15:03:22 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*int find_right_oper(char **mat)
{
    int	i;

	i = -1;
	while (mat[++i])
	{
		if (mat[i][0] == '>')
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
    while (sh->mat[++i])
    {
        if (sh->mat[i][0] == '>')
            sh->manager.file[j++] = sh->mat[i + 1];
    }
    sh->manager.file[j] = NULL;
}

void  get_dir(t_shell *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (sh->mat[++i])
    {
        if ((!ft_strncmp(sh->mat[i], ">", 1) &&  ft_strlen(sh->mat[i]) == 1) || (!ft_strncmp(sh->mat[i], ">>", 2) && ft_strlen(sh->mat[i]) == 2))
            sh->manager.redir[j++] = sh->mat[i];
    }
    sh->manager.redir[j] = NULL;
}

void  get_arg(t_shell *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (sh->mat[i])
    {
        if (sh->mat[i][0] != '>')
        {
            sh->manager.arg[j++] = sh->mat[i];
            i++;
        }
        else
            i += 2;
    }
    sh->manager.arg[j] = NULL;
    sh->mat = sh->manager.arg;
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
}*/

void process_redirection(t_shell *sh, char *str)
{
    int i = 0;
    int fd;

    // Encontra o operador de redirecionamento, como '>' ou '>>'
    while (str[i] && str[i] != '>' && str[i] != '<')
        i++;

    if (str[i] == '>' || str[i] == '<') {
        // Se for '>>', usa append (anexa ao arquivo existente)
        if (str[i + 1] && str[i + 1] == '>') {
            fd = open(str + i + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
            i += 2; // Avança para a posição após '>>'
        }
        else {
            fd = open(str + i + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            i += 1; // Avança para a posição após '>'
        }

        // Verifica se houve erro ao abrir o arquivo
        if (fd < 0) {
            perror("open");
            return;
        }

        // Redireciona a saída padrão (STDOUT) para o arquivo
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2");
            close(fd);
            return;
        }

        // Atualiza o shell para indicar que houve redirecionamento
        sh->redirect = 1;
        close(fd); // Fecha o arquivo após o redirecionamento
    }
}


void    redirects(t_shell *sh, t_args *args)
{
    int i;

    i = -1;
    while (args[++i].str)
    {
        process_redirection(sh, args[i].str);
    }
}