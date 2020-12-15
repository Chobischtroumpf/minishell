/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:41:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/13 15:12:19 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**the ft_new_cmd function will create a new t_cmd linked-list, malloc it, and
** initialize it
*/

static t_cmd	*ft_new_cmd(char *token)
{
	t_cmd	*new;

	if (!(new = malloc(sizeof(t_cmd))))
		ft_exit_error();
	if (token)
	{
		if (!(new->argv = malloc(sizeof(char *) * 2)))
			ft_exit_error();
		new->argv[0] = ft_strdup(token);
		new->argv[1] = NULL;
	}
	else
	{
		if (!(new->argv = malloc(sizeof(char *) * 1)))
			ft_exit_error();
		new->argv[0] = NULL;
	}
	new->pipe = 0;
	new->is_rdir = 0;
	if (ft_strchr(new->argv[0], '/'))
		new->has_path = 1;
	else
		new->has_path = 0;
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	return (new);
}

/*
** ft_add_pipe_cmd is a command that takes a t_cmd linked list as its first and
** only argument, and sets the pipe variable of it's last occurence to one
*/

static void		ft_add_pipe_cmd(t_cmd *cmd)
{
	t_cmd *last;

	last = ft_last_cmd(cmd);
	last->pipe = 1;
}

/*
** the ft_add_cmd function take a t_cmd linked list and the tokens as its
** arguments,and either adds a t_cmd element to the end of the linked-list or
** creates a new linked list
*/

static t_cmd	*ft_add_cmd(t_cmd *cmd, char *token)
{
	t_cmd	*tmp;

	if (!cmd)
		return (ft_new_cmd(token));
	else
	{
		tmp = cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_cmd(token);
	}
	return (cmd);
}

/*
** ft_add_argv_cmd takes a t_cmd linked list and arg as arguments, and adds the
** arg to the char** argument pointer on the last element of the linked-list
*/

static void		ft_add_argv_cmd(t_cmd *cmd, char *arg)
{
	t_cmd	*last;
	int		cnt;
	char	**new_arr;
	int		i;

	last = ft_last_cmd(cmd);
	cnt = ft_count_arg(last->argv);
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

/*
** the ft_cmd_parse function is a function that iterates through the tokens,
** and divides them into a t_cmd linked-list
*/

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
		if (new && !(new = 0))
			minishell->cmd = ft_add_cmd(minishell->cmd, NULL);
		if (!ft_strcmp(tokens[i], "|") && (new = 1))
			ft_add_pipe_cmd(minishell->cmd);
		else if (ft_is_redir(tokens[i]) && (++i))
			ft_add_redir_cmd(minishell->cmd, tokens[i - 1], tokens[i]);
		else if (!ft_strcmp(tokens[i], ";") && (new = 1) && (i++))
			continue;
		else
			ft_add_argv_cmd(minishell->cmd, tokens[i]);
		i++;
	}
	return (1);
}
