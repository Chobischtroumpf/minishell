/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:17:21 by ncolin            #+#    #+#             */
/*   Updated: 2020/11/02 10:13:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

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

void	ft_add_env(t_minishell *minishell, char **keyvalue)
{
	t_env *new_node;

	if (!(new_node = (t_env *)malloc(sizeof(t_env))))
		exit(0);
	new_node->key = ft_strdup(keyvalue[0]);
	new_node->value = ft_strdup(keyvalue[1]);
	new_node->next = NULL;
	ft_envadd_back(&minishell->env, new_node);
}

t_env	*ft_find_by_key(t_minishell *minishell, char *key)
{
	t_env *tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->key, key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
