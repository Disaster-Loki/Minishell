#include <stdlib.h>
#include <stdio.h>

char    *equals_end(char *str)
{
    int i;
    char    *result;

    i = 0;
    while (str[i] != '=' && str[i] != '\0')
        i++;
    result = malloc(sizeof(char) * (i + 1));
    if (!result)
        return (NULL);
    i = -1;
    while (str[++i] != '=' && str[i])
        result[i] = str[i];
    result[i] = '\0';
    return (result);
}

int main(int ac, char **av)
{
    printf("%s\n", equals_end("Figueredo="));
    return (0);
}