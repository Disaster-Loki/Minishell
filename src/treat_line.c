/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:58:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/22 16:58:21 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int find_quotes(t_shell *sh, int *start, int *end)
{
	int	i;

	i = *end + 1;
	while (sh->input[i])
	{
		if (sh->input[i] == '\"' || sh->input[i] == '\'')
		{
			*start = i;
			sh->in_q = sh->input[i];
			i++;
			while (sh->input[i] && sh->input[i] != sh->in_q)
				i++;
			if (sh->input[i] == sh->in_q)
			{
				*end = i;
				return (1);
			}
		}
		i++;
	}
    return (0);
}

void	final_str(t_shell *sh, int start, int end)
{
	char	*str;
	char	*str2;
	char	*rest;
	char	*temp;

	str = ft_substr(sh->input, 0, start);
	str2 = ft_substr(sh->input, start + 1, end - start - 1);
	rest = ft_substr(sh->input, end + 1, ft_strlen(sh->input) - end - 1);
	temp = ft_strjoin(str, str2);
	sh->input = ft_strjoin(temp, rest);
	free(str);
	free(str2);
	free(temp);
	free(rest);
}

void treat_line(t_shell *sh)
{
	int	start;
	int	end;

	start = -1;
	end = -1;
	while (find_quotes(sh, &start, &end))
		final_str(sh, start, end);
}
