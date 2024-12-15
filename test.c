#include <wait.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>

typedef struct s_shell
{
    char    *input;
    int     status;
}   t_shell;

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void ft_putstr_fd(char *s, int fd)
{
    if (s == NULL)
        return;
    write(fd, s, strlen(s));
}

char *strjoin(const char *s1, const char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result)
        return NULL;
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int is_empty_input(const char *input)
{
    while (*input)
    {
        if (*input != ' ' && *input != '\t')
            return 0;
        input++;
    }
    return 1;
}

int handle_syntax_error(char *token)
{
    ft_putstr_fd("bash: syntax error near unexpected token `", 2);
    if (!token || token[0] == '\0')
        ft_putstr_fd("newline", 2);
    else if (token[0] == '|' || token[0] == '<' || token[0] == '>')
    {
        if (token[1] && token[0] == token[1])
            ft_putchar_fd(token[0], 2);
        ft_putchar_fd(token[0], 2);
    }
    else
        ft_putstr_fd(token, 2);
    ft_putstr_fd("'\n", 2);
    return 258;
}

int herepipe(t_shell *sh)
{
    char *line;

    line = readline("> ");
    if (!line)
        return 0;
    char *new_input = strjoin(sh->input, line);
    free(sh->input);
    sh->input = new_input;
    free(line);
    return 1;
}

int check_pipe_syntax(t_shell *sh, char *input, int *i)
{
    int pipe_count = 1;

    (*i)++;
    while (input[*i] == '|')
    {
        pipe_count++;
        (*i)++;
    }
    while (input[*i] == ' ')
        (*i)++;

    if (pipe_count > 1 || input[*i] == '|')
        return handle_syntax_error("|");
    if (input[*i] == '\0')
        return herepipe(sh) ? 0 : 258;

    return 0;
}

int check_redirect_syntax(t_shell *sh, char *input, int *i)
{
    char redirect = input[*i];
    int count = 1;

    (*i)++;
    while (input[*i] == redirect)
    {
        count++;
        (*i)++;
    }
    if (count > 2 || (input[*i] == '<' || input[*i] == '>'))
        return handle_syntax_error(input + (*i) - count);
    while (input[*i] == ' ')
        (*i)++;

    if (input[*i] == '\0' || input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
        return handle_syntax_error(input + *i);

    return 0;
}

int syntax_characters(t_shell *sh, char *input, int *i)
{
    if (input[*i] == '|')
        return check_pipe_syntax(sh, input, i);
    if (input[*i] == '>' || input[*i] == '<')
        return check_redirect_syntax(sh, input, i);
    return 0;
}

int check_syntax_error(t_shell *sh)
{
    int i = 0;
    int status = 0;

    while (sh->input[i] == ' ') // Ignorar espaços no início
        i++;
    if (sh->input[i] == '|')
        return handle_syntax_error("|");

    while (sh->input[i]) 
    {
        status = syntax_characters(sh, sh->input, &i);
        if (status == 258)
            return 258;
        i++;
    }
    return 0;
}

int validate_input(t_shell *sh)
{
    if (is_empty_input(sh->input))
    {
        sh->status = 0;
        return -1;
    }
    int status = check_syntax_error(sh);
    if (status == 258)
        sh->status = status;
    return status;
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;

    (void)argc;
    (void)argv;
    (void)envp;
    shell.status = 0;
    while (1)
    {
        shell.input = readline("MiniShell-> ");
        if (!shell.input)
        {
            ft_putstr_fd("exit\n", 1);
            break;
        }
        if (!is_empty_input(shell.input))
            add_history(shell.input);

        validate_input(&shell);

        if (shell.status == 258)
            printf("input = %s\n", shell.input);
        else
            printf("input = %s\n", shell.input);

        free(shell.input);
    }
    return 0;
}
