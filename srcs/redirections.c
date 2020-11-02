/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:08:26 by alessandro        #+#    #+#             */
/*   Updated: 2020/10/29 12:11:42 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_redirection(t_cmd *cmd)
{
	t_rdir *last;

	if (cmd->in)
	{
		last = ft_last_rdir(cmd->in);
		last->std = dup(0);
		dup2(last->fd, 0);
	}
	if (cmd->out)
	{
		last = ft_last_rdir(cmd->out);
		last->std = dup(1);
		dup2(last->fd, 1);
	}
}

void	close_redirection(t_cmd *cmd)
{
	t_rdir	*last;

	if (cmd->in)
	{
		last = ft_last_rdir(cmd->in);
		dup2(last->std, 0);
		close(last->std);
	}
	if (cmd->out)
	{
		last = ft_last_rdir(cmd->out);
		dup2(last->std, 1);
		close(last->std);
	}	
}