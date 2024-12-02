/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: optimus-prime <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:13:56 by optimus-prime     #+#    #+#             */
/*   Updated: 2024/12/02 10:15:40 by optimus-prime    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;
    int status1;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    char *command1[] = {"/bin/ls", "-l", NULL};
    char *command2[] = {"/bin/wc", "-l", NULL};

    pid1 = fork();
    if (pid1 == 0)
    {
        close(pipe_fd[0]);
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            perror("dup2 falhou");
            exit(EXIT_FAILURE);
        }
        if (execve(command1[0], command1, NULL) == -1) {
            perror("execve comando 1 falhou");
            exit(EXIT_FAILURE);
        }
    }
    waitpid(pid1, &status1, 0);
    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipe_fd[1]);
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
            perror("dup2 falhou");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0)
            printf("O primeiro comando falhou, o segundo comando será executado com entrada vazia.\n");
        if (execve(command2[0], command2, NULL) == -1)
        {
            perror("execve comando 2 falhou");
            exit(EXIT_FAILURE);
        }
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid2, NULL, 0);

    return 0;
}
