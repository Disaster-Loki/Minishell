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
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 64
#define DELIM " \t\r\n\a"

void split_by_pipe(char *input, char **commands) {
    char *command = strtok(input, "|");
    int i = 0;
    while (command != NULL) {
        commands[i] = command;
        command = strtok(NULL, "|");
        i++;
    }
    commands[i] = NULL;
}

void split_by_space(char *input, char **args) {
    char *arg = strtok(input, DELIM);
    int i = 0;
    while (arg != NULL) {
        args[i] = arg;
        arg = strtok(NULL, DELIM);
        i++;
    }
    args[i] = NULL;
}

int main() {
    char *input;
    char *commands[2];
    char *args1[MAX_ARGS];
    char *args2[MAX_ARGS];
    int pipe_fd[2];
    pid_t pid1, pid2;
    int status1;

    while (1) {
        input = readline("ARGS: ");
        add_history(input);
        if (input == NULL) {
            printf("\n");
            exit(EXIT_FAILURE);
        }
        split_by_pipe(input, commands);
        if (commands[0] == NULL) {
            printf("Nenhum comando fornecido.\n");
            continue;
        }
        printf("command[0] = %s\n", commands[0]);
        printf("command[1] = %s\n", commands[1]);
        split_by_space(commands[0], args1);
        if (commands[1] != NULL) {
            split_by_space(commands[1], args2);
        }
        if (pipe(pipe_fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid1 = fork();
        if (pid1 == 0) {
            close(pipe_fd[0]);
            if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
                perror("dup2 falhou");
                exit(EXIT_FAILURE);
            }
            if (execve(args1[0], args1, NULL) == -1) {
                perror("execve comando 1 falhou");
                exit(EXIT_FAILURE);
            }
        }

        waitpid(pid1, &status1, 0);

        pid2 = fork();
        if (pid2 == 0) {
            close(pipe_fd[1]);
            if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
                perror("dup2 falhou");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0) {
                printf("O primeiro comando falhou, o segundo comando será executado com entrada vazia.\n");
            }

            if (execve(args2[0], args2, NULL) == -1) {
                perror("execve comando 2 falhou");
                exit(EXIT_FAILURE);
            }
        }

        close(pipe_fd[0]);
        close(pipe_fd[1]);

        waitpid(pid2, NULL, 0);

        free(input);
    }

    return 0;
}
