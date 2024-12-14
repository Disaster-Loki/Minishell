/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_rdir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:45:16 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:32 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_redirect(t_args *args, t_tokens *tok, char *rdir)
{
	if (ft_strcmp(args[tok->j].str, rdir) == 0
		&& (args[tok->j].id == 34 || args[tok->j].id == 39))
		return (1);
	return (0);
}

void	not_redirect(t_shell *sh, t_args *args, t_tokens *tok)
{
	if (is_valid_redirect(args, tok, ">")
		|| is_valid_redirect(args, tok, "<")
		|| is_valid_redirect(args, tok, ">>")
		|| is_valid_redirect(args, tok, "<<"))
		sh->n_rdir[tok->j] = 5;
}
