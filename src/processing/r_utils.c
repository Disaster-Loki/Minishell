/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/29 12:55:52 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_redirection_operator(char c)
{
	return (c == '<' || c == '>');
}

int	handle_quotes3(t_shell *sh, char *str, t_redir *redir)
{
	if (find_quotes(sh, str, &redir->start, &redir->end))
	{
		redir->i = redir->end;
		return (1);
	}
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*strjoin_and_free(char *s1, char *s2, char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*result;

	len1 = strlen(s1);
	len2 = strlen(s2);
	len3 = strlen(s3);
	result = malloc(len1 + len2 + len3 + 4);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	result[len1] = ' ';
	ft_strcpy(result + len1 + 1, s2);
	result[len1 + len2 + 1] = ' ';
	ft_strcpy(result + len1 + len2 + 2, s3);
	result[len1 + len2 + len3 + 2] = '\0';
	free(s1);
	free(s2);
	free(s3);
	return (result);
}
