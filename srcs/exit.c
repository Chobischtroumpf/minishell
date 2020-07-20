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
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;

	cmd = get_minishell()->cmd;
	free_line();
	free_tokens();
	while(cmd)
	{
		tmp = cmd->next;
		if(cmd->argv)
		{
			i = 0;
			while(cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		free_redir(cmd);
		free(cmd);
		cmd = tmp;
	}
	get_minishell()->cmd = 0;
}

void	free_all(void)
{
	ft_free_cmd();
}