/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 09:51:12 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/25 10:29:47 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** the ft_free_tokens function is in charge to free the minishell->tokens
** variable
*/

static void		ft_free_tokens(void)
{
	char	**tokens;
	int		i;

	tokens = get_minishell()->tokens;
	if (tokens)
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		get_minishell()->tokens = 0;
	}
}

/*
** the ft_free_line function is in charge to free the minishell->line variable
*/

static void		ft_free_line(void)
{
	if (get_minishell()->line)
		free(get_minishell()->line);
	get_minishell()->line = NULL;
}

/*
** the ft_free_redir function is in charge to free the t_rdir linked-list
** inside each t_cmd element
*/

static void		ft_free_redir(t_cmd *cmd)
{
	t_rdir *tmp;

	tmp = cmd->in;
	while (cmd->in)
	{
		free(cmd->in->file);
		tmp = cmd->in->next;
		free(cmd->in);
		cmd->in = tmp;
	}
	tmp = cmd->out;
	while (cmd->out)
	{
		free(cmd->out->file);
		tmp = cmd->out->next;
		free(cmd->out);
		cmd->out = tmp;
	}
}

/*
** the ft_free_cmd function is in charge to free the t_cmd linked-list
*/

void			ft_free_cmd(void)
{
	t_minishell	*minishell;
	t_cmd		*tmp;
	int			i;

	minishell = get_minishell();
	ft_free_line();
	ft_free_tokens();
	ft_free_env();
	while (minishell->cmd)
	{
		tmp = minishell->cmd->next;
		if (minishell->cmd->argv)
		{
			i = 0;
			while (minishell->cmd->argv[i])
				free(minishell->cmd->argv[i++]);
			free(minishell->cmd->argv);
		}
		ft_free_redir(minishell->cmd);
		free(minishell->cmd);
		minishell->cmd = tmp;
	}
	get_minishell()->cmd = 0;
}
