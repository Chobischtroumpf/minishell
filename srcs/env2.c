/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:17:21 by ncolin            #+#    #+#             */
/*   Updated: 2020/11/11 16:28:44 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Converts the linked_list storing the environement variables to a **char.
*/

char	**ft_env_to_array(void)
{
	t_minishell	*minishell;
	t_env		*tmp;
	char		**array;
	int			i;

	minishell = get_minishell();
	if (!(array = (char **)malloc(sizeof(char *) *\
							ft_envsize(minishell->env) + 1)))
		return (0);
	tmp = minishell->env;
	i = 0;
	while (tmp)
	{
		array[i] = ft_strjoin_delimiter(tmp->key, tmp->value, '=');
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

/*
**	Ft_add_env mallocs a new node initialize its values with the keyvalue 
**	**char passed as argument. It then adds it to the end of the env_list.
*/

void	ft_add_env(char **keyvalue)
{
	t_env *new_node;

	if (!(new_node = (t_env *)malloc(sizeof(t_env))))
		exit(0);
	new_node->key = ft_strdup(keyvalue[0]);
	new_node->value = ft_strdup(keyvalue[1]);
	new_node->next = NULL;
	ft_envadd_back(&get_minishell()->env, new_node);
}

void	ft_add_env2(char *key, char *value)
{
	t_env *new_node;

	if (!(new_node = (t_env *)malloc(sizeof(t_env))))
		exit(0);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	ft_envadd_back(&get_minishell()->env, new_node);
}

/*
**	Given the 'key' *char, ft_find_by_key will return a pointer to the node
**	containing that key. Returns NULL if nothing is found.
*/

t_env	*ft_find_by_key(char *key)
{
	t_env *tmp;

	tmp = get_minishell()->env;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->key, key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
**	Given the 'key' *char, ft_find_by_key will return the 'value' char of the
**	node containing that key. Returns NULL if nothing is found.
*/

char	*ft_find_by_key2(char *key)
{
	t_env *tmp;

	tmp = get_minishell()->env;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->key, key)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
