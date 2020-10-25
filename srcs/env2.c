/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:17:21 by ncolin            #+#    #+#             */
/*   Updated: 2020/10/25 12:09:17 by ncolin           ###   ########.fr       */
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

char	**env_to_array(void)
{
	t_minishell	*minishell;
	t_env		*tmp;
	char		**array;
	int			i;

	minishell = get_minishell();
	if (!(array = (char **)malloc(sizeof(char*) * \
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
** int ft_find_by_key(t_minishell *minishell, char *key)
** {
** 	t_list *tmp;
**
** 	tmp = minishell->env;
** 	while (tmp)
** 	{
** 		if (!(ft_strcmp(((t_env*)(tmp->content))->key, key)))
** 			return(1);
** 		tmp = tmp->next;
** 	}
** 	return (0);
** }
*/
