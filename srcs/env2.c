/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:17:21 by ncolin            #+#    #+#             */
/*   Updated: 2020/10/24 13:39:31 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void	free_node(t_list *node)
// {
// 	free(((t_env*)(node->content))->key);
// 	free(((t_env*)(node->content))->value);
// 	free(((t_env*)(node->content)));
// 	free(node);
// }

// int		ft_exec_unset(t_cmd *cmd)
// {	
// 	static t_minishell	*minishell;
// 	t_list		*tmp;
// 	t_list		*prev;
// 	char **args;
// 	int i;
	
// 	minishell = get_minishell();
// 	args = cmd->argv;
// 	i = 1;
// 	while (args[i])
// 	{
		
// 		tmp = minishell->env;
// 		printf("arg %s, key %s\n", args[i], ((t_env*)(tmp->next->content))->key);
// 		if (tmp && !ft_strcmp(((t_env*)(tmp->content))->key, args[i]))
// 		{
// 			minishell->env = tmp->next;
// 			free_node(tmp);
// 		}
// 		while(tmp && !ft_strcmp(((t_env*)(tmp->content))->key, args[i]))
// 		{
			
// 			prev = tmp;
// 			tmp = tmp->next;
// 		}
// 		if(tmp ==  NULL)
// 			return (0);
// 		prev->next = tmp->next;
// 		free_node(tmp);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

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