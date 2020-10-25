/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:30:41 by nathan            #+#    #+#             */
/*   Updated: 2020/10/24 00:27:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	ft_exec_env() mimics the env shell command. I goes through the env linked
**	list and prints each env_var's key, an '=' sign and the env_var value.
*/

int		ft_exec_env(void)
{
	t_minishell	*minishell;
	t_list		*tmp;

	minishell = get_minishell();
	tmp = minishell->env;
	while (tmp)
	{
		printf("%s=%s\n", ((t_env_var*)(tmp->content))->key,\
							((t_env_var*)(tmp->content))->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
