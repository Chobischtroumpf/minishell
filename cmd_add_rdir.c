/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_rdir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:35:09 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/13 16:22:10 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_rdir	*ft_new_rdir(char *file, int is_dbl)
{
	t_rdir *new;

	new = malloc(sizeof(t_rdir));
	new->file = ft_strdup(file);
	new->std = -1;
	new->is_dbl = is_dbl;
	new->next = NULL;
	return (new);
}

t_rdir			*ft_last_rdir(t_rdir *begin)
{
	while (begin->next)
		begin = begin->next;
	return (begin);
}


static t_rdir	*ft_add_rdir(t_rdir *begin, char *file, int is_dbl)
{
	t_rdir *last;

	if (!begin)
		return (ft_new_rdir(file, is_dbl));
	last = ft_last_rdir(begin);
	last->next = ft_new_rdir(file, is_dbl);
	return (begin);
}

void			ft_add_redir_cmd(t_cmd cmd,char *redir, char *file)
{
	t_cmd *last;

	last = ft_last_cmd(cmd);
	last->is_rdir = 1;
	if (!ft_strcmp(redir, "<"))
		last->in = ft_add_rdir(last->in, file, 0);
	else if (!ft_strcmp(redir, ">"))
		last->out = ft_add_rdir(last->out, file, 0);
	else if (!ft_strcmp(redir, ">>"))
		last->out = ft_add_rdir(last->out, file, 1);
}