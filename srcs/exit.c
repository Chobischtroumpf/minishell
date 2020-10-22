/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 09:51:12 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/20 16:43:07 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void			ft_free_line(void)
{
	if (get_minishell()->line)
		free(get_minishell()->line);
	get_minishell()->line = NULL;
}

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

void			ft_free_cmd(void)
{
	t_minishell	*minishell;
	t_cmd		*tmp;
	int			i;

	minishell = get_minishell();
	ft_free_line();
	ft_free_tokens();
	printf("cmd = %p\n", minishell->cmd);
	printf("minishell = %p\n", minishell);
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
