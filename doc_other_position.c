/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_other_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:51:53 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 17:04:16 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	more_than_tree_positions2(t_shell *sh)
{
	if (verify_status(sh))
	{
		when_ordered(sh);
	}
	else
	{
		when_unordered(sh);
	}
}

void	other_position(t_shell *sh)
{
	if (!sh->mat[3])
		tree_positions2(sh);
	else
		more_than_tree_positions2(sh);
}
