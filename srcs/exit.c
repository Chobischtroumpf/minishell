/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 09:51:12 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/15 15:19:22 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_tokens()
{
	char	**tokens;
	int		i;

	tokens = get_minishell()->tokens;
	if (tokens)
	{
		i = 0;
		while(tokens[i])
			free(tokens[i++]);
		free(tokens);
		get_minishell()->tokens = 0;
	}
}

void		free_line(void)
{
	if (get_minishell()->line)
		free(get_minishell()->line);
	get_minishell()->line = NULL;
}

static void	free_redir(t_cmd *cmd)
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

void		ft_free_cmd(void)
{
	t_minishell *minishell;
	t_cmd	*tmp;
	int		i;

	minishell = get_minishell();
	free_line();
	free_tokens();
	printf("cmd = %p\n", minishell->cmd);
	printf("minishell = %p\n", minishell);
	while(minishell->cmd)
	{
		tmp = minishell->cmd->next;
		if(minishell->cmd->argv)
		{
			i = 0;
			while(minishell->cmd->argv[i])
				free(minishell->cmd->argv[i++]);
			free(minishell->cmd->argv);
		}
		free_redir(minishell->cmd);
		free(minishell->cmd);
		minishell->cmd = tmp;
	}
	get_minishell()->cmd = 0;
}