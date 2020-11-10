/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:12:12 by ncolin            #+#    #+#             */
/*   Updated: 2020/11/10 09:19:25 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Compares the given string to the key of the given env node. 
**	Returns 0 if equal, 1 otherwise.
*/

int		ft_is_key(t_env *env, char *str)
{
	if (ft_strcmp(env->key, str))
		return (1);
	return (0);
}

/*
**	Given a certain key, will go through the envlist and return the
**	corresponding value. If the key isn't found, returns NULL.
*/

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

/*
**	Ft_remove_env will look through the env_list for 'key', deleted the node
**	and re-link the list.
*/

void	ft_remove_env(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*next;

	if (!(*env_list))
		return ;
	while (*env_list && ft_is_key(*env_list, key) == 0)
	{
		next = (*env_list)->next;
		free_node(*env_list);
		*env_list = next;
	}
	if (!(*env_list))
		return ;
	current = *env_list;
	while (current && current->next)
	{
		if (ft_is_key(current->next, key) == 0)
		{
			next = current->next->next;
			free_node(current->next);
			current->next = next;
		}
		else
			current = current->next;
	}
}

/*
**	Ft_exec_unset is the main function of the minishell unset command.
**	It verifies if the key(s) passed as argument(s) exist in the envlist
**	and removes them appropriatly.
*/

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
			ft_remove_env(&minishell->env, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
