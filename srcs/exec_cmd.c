/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:08:19 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/23 16:57:45 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**is_builtin
*/
static int	is_built_in(char *command)
{
	char **builtin;
	int i;

	i = 0;
	builtin = get_built_in();
	while (builtin[i])
	{
		if (!ft_strcmp(command, builtin[i]))
			return(i);
		i++;;
	}
	return (-1);
}

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
	else if (bltin_pos == 2)
		return (ft_exec_pwd());
	// if (bltin_pos == 3)
	// 	return (ft_exec_export());
	// if (bltin_pos == 4)
	// 	return (ft_exec_unset());
	else if (bltin_pos == 5)
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
	int		btin_nb;
	t_cmd	*cmd;

	get_minishell()->executed = 1;
	cmd = get_minishell()->cmd;
	while (cmd)
	{
		//check pipe
		if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
			ft_exec_builtin(btin_nb);
		else
			ft_exec_extern(cmd);
		cmd = cmd->next;
	}
	get_minishell()->executed = 0;
	return (1);
}
