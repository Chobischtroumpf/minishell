/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:41:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/14 14:59:58 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd			*ft_new_cmd(char *token)
{
	t_cmd	*new;

	if (!(new = malloc(sizeof(t_cmd))))
		exit_error();
	if (!(new->argv = malloc(sizeof(char *) * 2)))
		exit_error();
	new->argv[0] = ft_strdup(token);
	new->argv[1] = NULL;
	new->pipe = 0;
	new->is_rdir = 0;
	if (ft_strchr(new->argv[0], '/'))
		new->has_path = 1;
	else
		new->has_path = 0;
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	return(new);
}

static void		ft_add_pipe_cmd(t_cmd *cmd)
{
	t_cmd *last;
	
	last = ft_last_cmd(cmd);
	last->pipe = 1;
}

t_cmd			*ft_add_cmd(t_cmd *cmd, char *token)
{
	t_cmd	*tmp;

	if (!cmd)
		return(ft_new_cmd(token));
	else
	{
		tmp = cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_cmd(token);
	}
	return(cmd);
}

static void		ft_add_argv_cmd(t_cmd *cmd, char *arg)
{
	t_cmd	*last;
	int		cnt;
	char	**new_arr;
	int		i;

	last = ft_last_cmd(cmd);
	cnt = count_arg(last->argv);
	new_arr = malloc(sizeof(char*) * (cnt + 2));
	i = 0;
	while (i < cnt)
	{
		new_arr[i] = last->argv[i];
		i++;
	}
	new_arr[i] = ft_strdup(arg);
	new_arr[cnt + 1] = NULL;
	free(last->argv);
	last->argv = new_arr;
}

int				ft_cmd_parse(char **tokens)
{
	t_minishell	*minishell;
	int			i;
	int			new;

	if ((!ft_check_tokens(tokens)))
		return (0);
	minishell = get_minishell();
	minishell->cmd = 0;
	i = 0;
	new = 1;
	while (tokens[i])
	{
		printf("i : %d\n", i);
		if (new && !(new = 0))
			minishell->cmd = ft_add_cmd(minishell->cmd, tokens[i]);
		else if (!ft_strcmp(tokens[i], "|") && (new = 1))
			ft_add_pipe_cmd(minishell->cmd);
		else if (is_redir(tokens[i]) && (i++))
			ft_add_redir_cmd(minishell->cmd, tokens[i - 1], tokens[i]);
		else if (!ft_strcmp(tokens[i], ";") && (new = 1) && (i++))
			continue;
		else
			ft_add_argv_cmd(minishell->cmd, tokens[i]);
		i++;
	}
	return(1);
}
