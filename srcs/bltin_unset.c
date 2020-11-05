/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:12:12 by ncolin            #+#    #+#             */
/*   Updated: 2020/11/05 12:15:42 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env(t_env *env, char *str)
{
	if (ft_strcmp(env->key, str))
		return (1);
	return (0);
}

char	*ft_get_env_value(t_env *env_list, char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_remove_env(t_env *env_list, char *key)
{
	t_env	*current;
	t_env	*next;

	if (!env_list)
		return ;
	while (env_list && is_env(env_list, key) == 0)
	{
		next = env_list->next;
		free_node(env_list);
		env_list = next;
	}
	if (!env_list)
		return ;
	current = env_list;
	while (current && current->next)
	{
		if (is_env(current->next, key) == 0)
		{
			next = current->next->next;
			free_node(current->next);
			current->next = next;
		}
		else
			current = current->next;
	}
}

int		ft_exec_unset(t_cmd *cmd)
{
	static t_minishell	*minishell;
	char				**args;
	int					i;
	char				*value;

	minishell = get_minishell();
	args = cmd->argv;
	i = 1;
	while (args[i])
	{
		value = ft_get_env_value(minishell->env, args[i]);
		if (value)
			ft_remove_env(minishell->env, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
