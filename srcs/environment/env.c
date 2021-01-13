/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:07:45 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 16:11:16 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	ft_envadd_back adds the node 't_env *new' to the end of the linked list
**	that starts at 't_env **head'
*/

void	ft_envadd_back(t_env **head, t_env *new)
{
	t_env	*ptr;

	if (!*head)
		*head = new;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

/*
**	Ft_envsize returns the number of nodes in the given linked list.
*/

int		ft_envsize(t_env *env)
{
	int cnt;

	cnt = 1;
	while (env)
	{
		cnt++;
		env = env->next;
	}
	return (cnt);
}

/*
**	ft_free_env goes through the linked list containing the environnement
**	variables and frees every node.
*/

void	ft_free_env(void)
{
	t_minishell	*minishell;
	t_env		*tmp;

	minishell = get_minishell();
	tmp = minishell->env;
	while (minishell->env != NULL)
	{
		tmp = minishell->env;
		minishell->env = minishell->env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

/*
**	ft_free_array() frees every *char in a **char and then
**	frees the **char itself
*/

int		ft_free_array(char **array, int ret)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return (ret);
}

/*
** Allocate memory for a **char and store the environement
** variables inside.
*/

void	ft_init_env(t_minishell *minishell, char **envv)
{
	int			i;
	char		**key_value;
	t_env		*new_node;

	i = 0;
	while (envv[i])
	{
		if (!(key_value = ft_split_once(envv[i], '=')))
			ft_exit_error();
		if (!(new_node = (t_env *)ft_calloc(1, sizeof(t_env))))
			ft_exit_error();
		if (!(new_node->key = ft_strdup(key_value[0])))
			ft_exit_error();
		if (key_value[1])
		{
			if (!(new_node->value = ft_strdup(key_value[1])))
				ft_exit_error();
		}
		else if (!key_value[1])
			if (!(new_node->value = ft_strdup("")))
				ft_exit_error();
		ft_envadd_back(&minishell->env, new_node);
		ft_free_array(key_value, 0);
		i++;
	}
}
