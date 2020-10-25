/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:07:45 by nathan            #+#    #+#             */
/*   Updated: 2020/10/25 12:05:53 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		ft_envsize(t_env *env)
{
	int cnt;

	cnt = 0;
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

void	ft_free_array(char **array)
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
}

/*
** Allocate memory for a **char and store the environement
** variables inside.
*/

void	ft_init_env(t_minishell *minishell, char **envv)
{
	int			i;
	int			j;
	char		**key_value;
	char		*tmp;
	t_env		*new_node;

	i = 0;
	while (envv[i] && i < 3)
	{
		key_value = ft_split(envv[i], '=');
		if (!(new_node = (t_env *)malloc(sizeof(t_env))))
			exit(0);
		new_node->key = ft_strdup(key_value[0]);
		if (key_value[1])
		{
			tmp = ft_strdup(key_value[1]);
			j = 2;
			while (key_value[j])
			{
				tmp = ft_strjoin_delimiter(tmp, key_value[j], '=');
				j++;
			}
			new_node->value = ft_strdup(tmp);
			free(tmp);
		}
		else
			new_node->value = ft_strdup("");
		new_node->next = NULL;
		ft_envadd_back(&minishell->env, new_node);
		ft_free_array(key_value);
		i++;
	}
}
