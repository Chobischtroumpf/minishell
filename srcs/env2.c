/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:17:21 by ncolin            #+#    #+#             */
/*   Updated: 2020/10/24 17:13:15 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

// int ft_find_by_key(t_minishell *minishell, char *key)
// {
// 	t_list *tmp;

// 	tmp = minishell->env;
// 	while (tmp)
// 	{
// 		if (!(ft_strcmp(((t_env*)(tmp->content))->key, key)))
// 			return(1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }