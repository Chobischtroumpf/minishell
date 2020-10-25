/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:12:12 by ncolin            #+#    #+#             */
/*   Updated: 2020/10/24 17:21:26 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exec_unset(t_cmd *cmd)
{
	static t_minishell	*minishell;
	t_env				*tmp;
	t_env				*prev;
	char				**args;
	int					i;

	minishell = get_minishell();
	args = cmd->argv;
	i = 1;
	if (!(args[1]))//Should that be handled in cmd_parsing?
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (0);
	}
	while (args[i])
	{
		tmp = minishell->env;
		if (tmp && !ft_strcmp(tmp->key, args[i]))
		{
			minishell->env = tmp->next;
			free_node(tmp);
		}
		while (tmp && ft_strcmp(tmp->key, args[i]))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (!tmp)
			return (0);
		prev->next = tmp->next;
		free_node(tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
