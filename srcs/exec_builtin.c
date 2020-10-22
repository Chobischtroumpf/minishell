/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:08:19 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/22 21:26:53 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** executes the specified builtin command, depending on the bltin_pos variable's value
*/

static int	ft_exec_builtin(int bltin_pos)
{
	t_minishell *minishell;

	minishell = get_minishell();
	if (bltin_pos == 0)
		return (ft_exec_echo(minishell->cmd));
	// if (bltin_pos == 1)
	// 	return (ft_exec_cd());
	if (bltin_pos == 2)
		return (ft_exec_pwd());
	// if (bltin_pos == 3)
	// 	return (ft_exec_export());
	// if (bltin_pos == 4)
	// 	return (ft_exec_unset());
	if (bltin_pos == 5)
		return (ft_exec_env());
	// if (bltin_pos == 6)
		return (ft_exec_exit(minishell->cmd));
	return (0);
}

/*
** ft_exec_cmd is the command in charge of executing the different comands
** found in the t_cmd struct
*/

int			ft_exec_cmd(void)
{
	char	**builtin;
	int		i;
	int		ret;

	ret = 1;
	i = -1;
	builtin = get_built_in();
	get_minishell()->executed = 1;
	while (++i < 7)
		if (!ft_strcmp(builtin[i], get_minishell()->cmd->argv[0]))
		{
			ret = ft_exec_builtin(i);
			break ;
		}
	get_minishell()->executed = 0;
	if (ret == 1)
	{
		ft_printf("minishell : command not found : %s\n",
						get_minishell()->cmd->argv[0]);
		return (0);
	}
	else
		return (ret);
}
