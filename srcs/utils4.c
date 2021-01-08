/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:02:38 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/08 23:18:24 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_chardup(char c)
{
	char *dup;

	if (!(dup = (char *)ft_calloc(2, sizeof(char))))
	{
		ft_exit_error();
		return (NULL);
	}
	dup[0] = c;
	return (dup);
}

int		count_pipes(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		if (cmd->pipe)
			i++;
		else
			break ;
		cmd = cmd->next;
	}
	return (i);
}

void	ft_free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

char	*ft_last_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (arg[i - 1]);
}
