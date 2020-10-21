/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_rdir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:35:09 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/21 13:35:07 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** the ft_new_rdir function creates a t_rdir linked list
*/

static t_rdir	*ft_new_rdir(char *file, int is_dbl)
{
	t_rdir *new;

	if (!(new = malloc(sizeof(t_rdir))))
		return (exit_error());
	new->file = ft_strdup(file);
	new->std = -1;
	new->is_dbl = is_dbl;
	new->next = NULL;
	return (new);
}

/*
** iterates through the t_rdir linked list until its last element, and then
** return it
*/

t_rdir			*ft_last_rdir(t_rdir *begin)
{
	while (begin->next)
		begin = begin->next;
	return (begin);
}

/*
** ft_add_rdir is a function that adds an element at the end of the t_rdir
** linked list
*/

static t_rdir	*ft_add_rdir(t_rdir *begin, char *file, int is_dbl)
{
	t_rdir *last;

	if (!begin)
		return (ft_new_rdir(file, is_dbl));
	last = ft_last_rdir(begin);
	last->next = ft_new_rdir(file, is_dbl);
	return (begin);
}

/*
** ft_add_redir is the function in charge of adding the redirection linked list
** to the the cmd, depending on which redirection was used
*/

void			ft_add_redir_cmd(t_cmd *cmd, char *redir, char *file)
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
