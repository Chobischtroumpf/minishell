/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:12:12 by ncolin            #+#    #+#             */
/*   Updated: 2020/11/27 12:02:46 by nathan           ###   ########.fr       */
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

int		ft_remove_env(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*next;

	while (*env_list && ft_is_key(*env_list, key) == 0)
	{
		next = (*env_list)->next;
		ft_free_node(*env_list);
		*env_list = next;
		return (0);
	}
	if (!(*env_list))
		return (0);
	current = *env_list;
	while (current && current->next)
	{
		if (ft_is_key(current->next, key) == 0)
		{
			next = current->next->next;
			ft_free_node(current->next);
			current->next = next;
		}
		else
			current = current->next;
	}
	return (0);
}

int		ft_valid_key2(char *str)
{
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	if (!tmp[i])
		return (0);
	while (tmp[i])
	{
		if (!ft_isalnum(tmp[i]))
			return (0);
		if (ft_isspace(tmp[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
**	Ft_exec_unset is the main function of the minishell unset command.
**	It verifies if the key(s) passed as argument(s) exist in the envlist
**	and removes them appropriatly.
*/

int		ft_exec_unset(t_cmd *cmd)
{
	char				**args;
	int					i;
	char				*value;
	int					ret;
	int					fail;

	args = cmd->argv;
	i = 1;
	ret = 1;
	fail = 0;
	value = NULL;
	while (args[i])
	{
		if (ft_valid_key2(args[i]))
			value = ft_get_env_value(get_minishell()->env, args[i]);
		else
			fail = ft_invalid_identifier("unset", args[i]);
		if (value)
			ret &= ft_remove_env(&get_minishell()->env, args[i]);
		i++;
	}
	if ((ret || fail) && i > 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
