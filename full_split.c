/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:19 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:21 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_token(t_split *spt, int start)
{
	return (ft_substr(spt->str, start, spt->i - start));
}

int	process_segment(t_shell *sh, t_split *spt, char delt)
{
	int	end;
	int	start;

	start = spt->i;
	while (spt->str[spt->i] && spt->str[spt->i] != delt)
	{
		if (spt->str[spt->i] == '\'' || spt->str[spt->i] == '\"')
		{
			if (handle_quotes2(sh, spt, &end))
				return (1);
		}
		spt->i++;
	}
	if (spt->i > start)
		spt->res[spt->idx++] = extract_token(spt, start);
	return (0);
}

char	**full_split(t_shell *sh, char *str, char c)
{
	t_split	spt;

	if (initialize_split(&spt, str))
		return (free(spt.res), NULL);
	while (spt.str[spt.i])
	{
		if (process_segment(sh, &spt, c))
		{
			free(spt.res);
			return (NULL);
		}
		if (spt.str[spt.i] == c)
			spt.i++;
	}
	spt.res[spt.idx] = NULL;
	return (spt.res);
}
